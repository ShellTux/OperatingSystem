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

#include "message-queue-store-cashier.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

int messageQueueID;

int main(void)
{
	if ((messageQueueID = msgget(IPC_PRIVATE, IPC_CREAT | 0600)) == -1) {
		perror("msgget: ");
		exit(EXIT_FAILURE);
	}

	signal(SIGINT, cleanup);
	signal(SIGHUP, cleanup);
	signal(SIGQUIT, cleanup);
	signal(SIGTERM, cleanup);

	for (int i = 0; i < CASHIER_NUM; ++i) {
		if (fork() == 0) {
			cashierWork(i);
			exit(EXIT_SUCCESS);
		}
	}

	for (int i = 0; i < 10; ++i) {
		const size_t cashierID = RANDINT(0, CASHIER_NUM);
		MessageQueueMessage message = {
		    .messageType = cashierID,

		    .customerID = i,
		    .products = CUSTOMER_PRODUCTS,
		};
		printf("Customer %zu arrived and selected cashier %zu (%zu products).\n",
				message.customerID,
				cashierID,
				message.products);
		msgsnd(messageQueueID,
		       &message,
		       sizeof(message) - sizeof(long),
		       0);
		sleep(CUSTOMER_INTERVAL);
	}

	cleanup(0);

	pid_t status;
	while ((status = wait(NULL)) != -1) {}

	return 0;
}

void cleanup(const int signalN)
{
	(void) signalN;
	msgctl(messageQueueID, IPC_RMID, NULL);
	// NOTE: Guarantees that every process receives a SIGTERM
	/* kill(0, SIGTERM); */
	exit(EXIT_SUCCESS);
}

void cashierWork(const int cashierID)
{
	printf("Cashier %d open!\n", cashierID);

	MessageQueueMessage message;
	msgrcv(messageQueueID,
	       &message,
	       sizeof(message) - sizeof(long),
	       cashierID,
	       0);

	printf("> Cashier %d handling customer %zu (%zu products).\n",
	       cashierID,
	       message.customerID,
	       message.products);
	sleep(1);
}
