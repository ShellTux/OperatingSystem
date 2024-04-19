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

#include "producer-consumer.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Define the shared buffer
int buffer[BUFFER_SIZE] = {0};
int writePosition       = 0;
int readPosition        = 0;

// Define semaphores
sem_t empty;
sem_t full;

// Define mutex
pthread_mutex_t mutex;

int main(void)
{
	// NOTE: Initialize semaphores
	if (sem_init(&empty, 0, BUFFER_SIZE) == -1) {
		perror("Error initializing semaphore empty: ");
		exit(EXIT_FAILURE);
	}

	if (sem_init(&full, 0, 0) == -1) {
		perror("Error initializing semaphore full: ");
		exit(EXIT_FAILURE);
	}

	// NOTE: Initialize mutex
	if (pthread_mutex_init(&mutex, NULL) != 0) {
		perror("Pthread mutex init: ");
		exit(EXIT_FAILURE);
	}

	pthread_t producerThread;
	pthread_t consumerThread;

	// NOTE: Create producer and consumer threads
	if (pthread_create(&producerThread, NULL, producer, NULL) != 0) {
		perror("Error creating producer Thread: ");
		exit(EXIT_FAILURE);
	}

	if (pthread_create(&consumerThread, NULL, consumer, NULL) != 0) {
		perror("Error creating consumer Thread: ");
		exit(EXIT_FAILURE);
	}

	// NOTE: Join threads
	pthread_join(producerThread, NULL);
	pthread_join(consumerThread, NULL);

	// NOTE: Destroy semaphores and mutex
	sem_destroy(&empty);
	sem_destroy(&full);
	pthread_mutex_destroy(&mutex);

	return 0;
}

void *producer(void *argument)
{
	(void) argument;
	loopN(TOTAL_VALUES)
	{
		// Produce item
		int item = rand() % MAX;
		printf("[PRODUCER]: Writing %d\n", item);
		putElement(item);
	}

	pthread_exit(NULL);
}

void *consumer(void *argument)
{
	(void) argument;
	loopN(TOTAL_VALUES)
	{
		// Consume item
		const int item = getElement();
		printf("[CONSUMER]: Retrieved %d\n", item);
		usleep(CONSUMER_WAIT);
	}

	pthread_exit(NULL);
}

void putElement(const int element)
{
	// Wait for empty semaphore
	sem_wait(&empty);

	// Acquire mutex
	pthread_mutex_lock(&mutex);

	// Add item to buffer
	buffer[writePosition] = element;
	writePosition         = (writePosition + 1) % BUFFER_SIZE;

	// Release mutex
	pthread_mutex_unlock(&mutex);

	// Signal full semaphore
	sem_post(&full);
}

int getElement(void)
{
	// Wait for full semaphore
	sem_wait(&full);

	// Acquire mutex
	pthread_mutex_lock(&mutex);

	// Remove item from buffer
	const int item = buffer[readPosition];
	readPosition   = (readPosition + 1) % BUFFER_SIZE;

	// Release mutex
	pthread_mutex_unlock(&mutex);

	// Signal empty semaphore
	sem_post(&empty);

	return item;
}
