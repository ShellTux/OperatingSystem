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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define N_FORKS 10

int main(void)
{
	srand(time(NULL));

	for (int i = 0; i < N_FORKS; ++i) {
		int sleepTime = 1 + rand() % 10;
		int pid       = fork();

		if (pid == -1) {
			perror("Fork Error: ");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			// NOTE: CHILD CODE
			sleep(sleepTime);
			printf("Child ID: %d, Child PID: %d, Child PPID: %d\n",
			       pid,
			       getpid(),
			       getppid());
			exit(EXIT_SUCCESS);
		} else {
			// NOTE: MAIN CODE
			printf("New Process generated with PID: %d, with sleep "
			       "time of %d\n",
			       pid,
			       sleepTime);
		}
	}

	pid_t status;
	while ((status = wait(NULL)) != -1) {
		printf("Finished execution of PID: %d\n", status);
	}

	return 0;
}
