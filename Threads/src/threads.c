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

#include "threads.h"

#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
	srand(time(NULL));

	Thread threads[N_THREADS] = {0};
	for (int i = 0; i < N_THREADS; ++i) {
		threads[i].id = i + 1;

		srand(i);
		threads[i].workTime = 1 + rand() % MAX_SLEEP;

		pthread_create(
				&threads[i].threadID,
				NULL,
				threadFunction,
				&threads[i]
			      );
	}

	for (int i = 0; i < N_THREADS; ++i) {
		pthread_join(threads[i].threadID, NULL);
	}

	pthread_exit(NULL);

	return 0;
}

void *threadFunction(void *argument)
{
	Thread thread = *(Thread *) argument;

	printf("[%02zu] Thread, start working for %zu seconds...\n", thread.id, thread.workTime);

	sleep(thread.workTime);

	printf("[%02zu] Thread, end working...\n", thread.id);

	pthread_exit(NULL);
}
