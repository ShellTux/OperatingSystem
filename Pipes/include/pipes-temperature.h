#ifndef PIPES_PIPES_TEMPERATURE_H
#define PIPES_PIPES_TEMPERATURE_H

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

#define PIPE_NAME "user_temperature_pipe"

#define TEMPERATURE_MIN           10
#define TEMPERATURE_MAX           40
#define HUMIDITY_MIN              50
#define HUMIDITY_MAX              100
#define POLL_INTERVAL_MILISECONDS 500
#define N_POLLS                   10
#define RANDINT(MIN, MAX)         (rand() % (MAX - MIN) + MIN)

void server(void);
void temperatureReader(void);
void humidityReader(void);

#endif // !PIPES_PIPES_TEMPERATURE_H
