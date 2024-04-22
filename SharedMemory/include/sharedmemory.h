#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

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

#define MICRO2MILI(MICRO) (MICRO * 1000)
#define RANDINT(MIN, MAX) (rand() % (MAX - MIN) + MIN)

#define LOREM                                                                  \
	"Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do "    \
	"eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim " \
	"ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "  \
	"aliquip ex ea commodo consequat. Duis aute irure dolor in "           \
	"reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla " \
	"pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "   \
	"culpa qui officia deserunt mollit anim id est laborum."

void child(const unsigned int sleepTime);

#endif // !SHARED_MEMORY_H
