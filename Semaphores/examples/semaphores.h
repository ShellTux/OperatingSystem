#ifndef SEMAPHORES_EXAMPLES_SEMAPHORES_H
#define SEMAPHORES_EXAMPLES_SEMAPHORES_H

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

#define N_FORKS 10
#define handle_error(msg)           \
	do {                        \
		perror(msg);        \
		exit(EXIT_FAILURE); \
	} while (0)

#define NAMED   1
#define UNNAMED 2

#define SEMAPHORE_NAME          "NAMED_SEMAPHORE"
#define SEMAPHORE_DEFAULT_VALUE 0
#define PSHARED                 0
#define SEMAPHORE               NAMED

void initializeSemaphores(void);
void terminateSemaphores(void);
void worker(void);

#endif // !SEMAPHORES_EXAMPLES_SEMAPHORES_H
