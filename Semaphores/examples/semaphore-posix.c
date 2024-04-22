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

#include "semaphores.h"

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

sem_t unnamed;
sem_t *named;

int main(void)
{
	initializeSemaphores();

	for (int i = 0; i < N_FORKS; ++i) {
		int childID = fork();
		if (childID == 0) {
			worker();
			exit(EXIT_SUCCESS);
		} else if (childID == -1) {
			perror("fork Error: ");
			exit(EXIT_FAILURE);
		}
	}

	terminateSemaphores();

	return 0;
}

void initializeSemaphores(void)
{
#if SEMAPHORE == NAMED
	if (sem_unlink(SEMAPHORE_NAME) == -1) {
		handle_error("Error sem_unlink: ");
	}
	if (sem_open(SEMAPHORE_NAME,
	             O_CREAT | O_EXCL,
	             0600,
	             SEMAPHORE_DEFAULT_VALUE)
	    == SEM_FAILED) {
		handle_error("Error sem_open: ");
	}
#elif SEMAPHORE == UNNAMED
	if (sem_init(&unnamed, PSHARED, SEMAPHORE_DEFAULT_VALUE) == -1) {
		handle_error("Error sem_init: ");
	}
#endif
}

void terminateSemaphores(void)
{
#if SEMAPHORE == NAMED
	sem_close(named);
	sem_unlink(SEMAPHORE_NAME);
#elif SEMAPHORE == UNNAMED
	sem_destroy(&unnamed);
#endif
}

void worker(void)
{
#if SEMAPHORE == NAMED
	sem_wait(named);
	// Work
	sem_post(named);
#elif SEMAPHORE == UNNAMED
	sem_wait(&unnamed);
	// Work
	sem_post(&unnamed);
#endif
}
