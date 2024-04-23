#ifndef MESSAGE_QUEUE_MESSAGE_QUEUE_STORE_CASHIER_H
#define MESSAGE_QUEUE_MESSAGE_QUEUE_STORE_CASHIER_H

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

#define CASHIER_NUM 10

#define RANDINT(MIN, MAX)       (rand() % (MAX - MIN) + MIN)
/* #define CUSTOMER_INTERVAL       RANDINT(2, 10) */
#define CUSTOMER_INTERVAL       RANDINT(1, 2)
#define CUSTOMER_PRODUCTS       RANDINT(2, 10)
#define CASHIER_PROCESS_SECONDS 1

typedef struct {
	long messageType;

	size_t customerID;
	size_t products;
} MessageQueueMessage;

void cleanup(const int signalN);
void cashierWork(const int cashierID);

#endif // !MESSAGE_QUEUE_MESSAGE_QUEUE_STORE_CASHIER_H
