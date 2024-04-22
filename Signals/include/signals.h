#ifndef SIGNALS_SIGNALS_H
#define SIGNALS_SIGNALS_H

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

#include <stddef.h>

#define MAX_SIGNALS 10
#define GAME_INTRO                                                           \
	"Time Game\n"                                                        \
	"You will be given a time in seconds and you will try to match the " \
	"clock by pressing Ctrl+c to match the time\n"                       \
	"\nExample:\n"                                                       \
	"Press Ctrl+c in 7 seconds!\n\n"                                     \
	"  - Ctrl+z: Quit Game\n"                                            \
	"  - Ctrl+c: Play Game\n"
#define GAME_TURN_FORMAT  "Press Ctrl+c in %zu seconds\n"
#define RANDINT(MIN, MAX) (rand() % (MAX - MIN) + MIN)

void countdown(size_t countdown);
void sigTSTPHandler(const int signalN);
void printGlobal(void);
void gameIntro(void);
void playGame(const int signalN);
void quitGame(const int signalN);
void confirmQuitGame(const int signalN);
void calculateDelta(const int signalN);

#endif // !SIGNALS_SIGNALS_H
