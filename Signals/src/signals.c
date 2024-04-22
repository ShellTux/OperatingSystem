/*******************************************************************************
 * Project    ___                     _   _           ___         _
 *           / _ \ _ __  ___ _ _ __ _| |_(_)_ _  __ _/ __|_  _ __| |_ ___ _ __
 *          | (_) | '_ \/ -_) '_/ _` |  _| | ' \/ _` \__ \ || (_-<  _/ -_) '  \
 *           \___/| .__/\___|_| \__,_|\__|_|_||_\__, |___/\_, /__/\__\___|_|_|_|
 *                |_|                           |___/     |__/
 *
 *
 * Author: Luís Góis
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the LICENSE file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

#include "signals.h"

#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int global = 0;
size_t deltaTime;

int main(void)
{
	srand(time(NULL));

	gameIntro();

	return 0;
}

void sigTSTPHandler(const int signalN)
{
	(void) signalN;
	printGlobal();
}

void printGlobal(void)
{
	printf("global = %d\n", ++global);
}

void gameIntro(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);

	printf(GAME_INTRO);

	signal(SIGINT, playGame);
	signal(SIGTSTP, quitGame);
	pause();
}

void countdown(size_t countdown)
{
	sigset_t blockedSignalSet = {0};
	sigemptyset(&blockedSignalSet);
	sigaddset(&blockedSignalSet, SIGINT);

	sigprocmask(SIG_BLOCK, &blockedSignalSet, NULL);
	while (countdown > 0) {
		printf("\rCountdown: %zu ...", countdown--);
		fflush(stdout);
		sleep(1);
	}
	sigprocmask(SIG_UNBLOCK, &blockedSignalSet, NULL);

	printf("\n");
}

void playGame(const int signalN)
{
	(void) signalN;
	signal(SIGTSTP, confirmQuitGame);

	sigset_t blockedSignalSet = {0};
	sigemptyset(&blockedSignalSet);
	sigaddset(&blockedSignalSet, SIGTSTP);

	while (1) {
		signal(SIGINT, SIG_IGN);

		sigprocmask(SIG_BLOCK, &blockedSignalSet, NULL);
		const size_t timeSeconds = RANDINT(3, 10);
		printf(GAME_TURN_FORMAT, timeSeconds);
		countdown(3);
		deltaTime = time(NULL);

		signal(SIGINT, calculateDelta);
		pause();
		sigprocmask(SIG_UNBLOCK, &blockedSignalSet, NULL);

		printf(" pressed in %zu\n\n", deltaTime);
	}
}

void quitGame(const int signalN)
{
	(void) signalN;
	printf("Ok, Bye bye!\n");
	exit(EXIT_SUCCESS);
}

void confirmQuitGame(const int signalN)
{
	(void) signalN;
	printf(" pressed. Do you want to Quit? (y = yes) ");
	if (getchar() == 'y') {
		quitGame(signalN);
	}
}

void calculateDelta(const int signalN)
{
	(void) signalN;
	deltaTime = time(NULL) - deltaTime;
}
