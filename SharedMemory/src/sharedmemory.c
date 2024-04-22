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

#include "sharedmemory.h"

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int sharedMemoryID;
int *sharedVariable = NULL;

#if SEMAPHORE == NAMED_SEMAPHORE
sem_t *namedSemaphore = NULL;
#elif SEMAPHORE == UNNAMED_SEMAPHORE
sem_t unnamedSemaphore;
#endif

int main(void)
{
	srand(time(NULL));

	sharedMemoryID
	    = shmget(IPC_PRIVATE, sizeof(*sharedVariable), IPC_CREAT | 0600);
	if (sharedMemoryID == -1) {
		perror("IPC shmget: ");
		exit(EXIT_FAILURE);
	}

#if SEMAPHORE == NAMED_SEMAPHORE
	sem_unlink(MUTEX);
	namedSemaphore = sem_open(MUTEX, O_CREAT | O_EXCL, 0600, 1);
	if (namedSemaphore == SEM_FAILED) {
		perror("IPC ERROR sem_open: ");
		exit(EXIT_FAILURE);
	}
#elif SEMAPHORE == UNNAMED_SEMAPHORE
	if (sem_init(&unnamedSemaphore, 1, 1) == -1) {
		perror("IPC ERROR sem_init: ");
		exit(EXIT_FAILURE);
	}

	sem_post(&unnamedSemaphore);
#endif

	if ((sharedVariable = shmat(sharedMemoryID, NULL, 0)) == (void *) -1) {
		perror("IPC ERROR shmat: ");
		exit(EXIT_FAILURE);
	}

	*sharedVariable = 0;

	shmdt(sharedVariable);

	printf("[INFO]: Creating %d new processes\n", N_FORKS);
	for (int i = 0; i < N_FORKS; ++i) {
		const unsigned int sleepTime = RANDINT(1, 10) * 1e5;

		const int childID = fork();
		if (childID == 0) {
			worker(sleepTime);
			exit(EXIT_SUCCESS);
		} else if (childID == -1) {
			perror("fork: ");
			exit(EXIT_FAILURE);
		}
	}

	if ((sharedVariable = shmat(sharedMemoryID, NULL, SHM_RDONLY))
	    == (void *) -1) {
		perror("IPC ERROR shmat: ");
		exit(EXIT_FAILURE);
	}

	pid_t status;
	while ((status = wait(NULL)) != -1) {}

	printf("sharedVariable = %d\n", *sharedVariable);

#if SEMAPHORE == NAMED_SEMAPHORE
	sem_close(namedSemaphore);
	sem_unlink(MUTEX);
#elif SEMAPHORE == UNNAMED_SEMAPHORE
	sem_destroy(&unnamedSemaphore);
#endif

	shmdt(sharedVariable);
	shmctl(sharedMemoryID, IPC_RMID, NULL);

	return 0;
}

void worker(const unsigned int sleepTime)
{
	if ((sharedVariable = shmat(sharedMemoryID, NULL, 0)) == (void *) -1) {
		perror("IPC shmat: ");
		exit(EXIT_FAILURE);
	}

#if SEMAPHORE == NAMED_SEMAPHORE
	(void) sleepTime;
	sem_wait(namedSemaphore);
	(*sharedVariable)++;
	sem_post(namedSemaphore);
#elif SEMAPHORE == UNNAMED_SEMAPHORE
	(void) sleepTime;
	sem_wait(&unnamedSemaphore);
	(*sharedVariable)++;
	sem_post(&unnamedSemaphore);
#else
	usleep(sleepTime);
	(*sharedVariable)++;
#endif

	shmdt(sharedVariable);

	exit(EXIT_SUCCESS);
}
