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

#include "pipes-temperature.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int temperaturePipe[2] = {0};
int humidityPipe[2]    = {0};

int main(void)
{
	srand(time(NULL));

	if ((mkfifo(PIPE_NAME, O_CREAT | O_EXCL | 0600) < 0)
	    && (errno != EEXIST)) {
		perror("mkfifo: ");
		exit(0);
	}

	if (pipe(temperaturePipe) == -1) {
		perror("pipe: ");
		exit(EXIT_FAILURE);
	}

	const size_t temperatureDelay = RANDINT(10, 50) * 1e5;
	const size_t humidityDelay    = rand() % 5;

	if (fork() == 0) {
		usleep(temperatureDelay);
		temperatureReader();
		exit(EXIT_SUCCESS);
	}

	if (pipe(humidityPipe) == -1) {
		perror("pipe: ");
		exit(EXIT_FAILURE);
	}

	if (fork() == 0) {
		usleep(humidityDelay);
		humidityReader();
		exit(EXIT_SUCCESS);
	}

	server();

	pid_t status;
	while ((status = wait(NULL)) != -1) {}

	unlink(PIPE_NAME);

	return 0;
}

void server(void)
{
	close(temperaturePipe[1]);
	close(humidityPipe[1]);

	// TODO: Implement select
	size_t temperature;
	size_t humidity;
	int bytes = -1;
	do {
		fd_set readSet = {0};
		FD_ZERO(&readSet);
		FD_SET(temperaturePipe[0], &readSet);
		FD_SET(humidityPipe[0], &readSet);

		if (select(humidityPipe[0] + 1, &readSet, NULL, NULL, NULL)
		    == -1) {
			perror("select: ");
			break;
		}

		if (FD_ISSET(temperaturePipe[0], &readSet)) {
			bytes = read(temperaturePipe[0],
			             &temperature,
			             sizeof(temperature));
			printf("[SERVER] Received Temperature: %zu\n",
			       temperature);
		} else if (FD_ISSET(humidityPipe[0], &readSet)) {
			bytes = read(humidityPipe[0],
			             &humidity,
			             sizeof(humidity));
			printf("[SERVER] Received Humidity: %zu\n", humidity);
		}

	} while (bytes > 0);
}

void temperatureReader(void)
{
	close(temperaturePipe[0]);
	for (int i = 0; i < N_POLLS; ++i) {
		const size_t randomTemperature
		    = RANDINT(TEMPERATURE_MIN, TEMPERATURE_MAX);
		write(temperaturePipe[1],
		      &randomTemperature,
		      sizeof(randomTemperature));
		usleep(POLL_INTERVAL_MILISECONDS * 1e3);
	}
}

void humidityReader(void)
{
	close(humidityPipe[0]);
	for (int i = 0; i < N_POLLS; ++i) {
		const size_t randomHumidity
		    = RANDINT(HUMIDITY_MIN, HUMIDITY_MAX);
		write(humidityPipe[1], &randomHumidity, sizeof(randomHumidity));
		usleep(POLL_INTERVAL_MILISECONDS * 1e3);
	}
}
