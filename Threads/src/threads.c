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

#include "Matrix.h"

#include <bits/time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Matrix matrixA = {0};
Matrix matrixB = {0};
Matrix matrixC = {0};

int main(void)
{
	srand(time(NULL));

	matrixA = createMatrix(M, K);
	matrixB = createMatrix(K, N);

	generateRandomMatrix(&matrixA, MIN, MAX);
	generateRandomMatrix(&matrixB, MIN, MAX);

	matrixC = matrixMultiplication(matrixA, matrixB);

	if (M <= 10 && K <= 10 && N <= 10) {
		printf("A: ");
		printMatrix(matrixA);

		printf("B: ");
		printMatrix(matrixB);

		printf("C = A * B = ");
		printMatrix(matrixC);
	}

	return 0;
}
