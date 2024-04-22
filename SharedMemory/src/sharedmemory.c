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

int main(void)
{
	srand(time(NULL));

	sharedMemoryID = shmget(IPC_PRIVATE, sizeof(*sharedVariable), IPC_CREAT | 0600);
	if (sharedMemoryID == -1) {
		perror("IPC shmget: ");
		exit(EXIT_FAILURE);
	}

	printf("[INFO]: Creating %d new processes\n", N_FORKS);
	for (int i = 0; i < N_FORKS; ++i) {
		const unsigned int sleepTime = RANDINT(1, 10);
		if (fork() == 0) {
			child(sleepTime);
			exit(EXIT_SUCCESS);
		}
	}

	shmctl(sharedMemoryID, IPC_RMID, NULL);

	pid_t status;
	while ((status = wait(NULL)) != -1) {}

	return 0;
}

void child(const unsigned int sleepTime)
{
	/* shmat(sharedMemoryID, ) */
	exit(EXIT_SUCCESS);
}
