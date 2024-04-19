#ifndef THREADS_MATRIX_H
#define THREADS_MATRIX_H

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

typedef struct {
	size_t rows;
	size_t cols;
	int *data;
} Matrix;

#define BENCHMARK 0
#if BENCHMARK == -1
#define M 2
#define K 3
#define N 2
#elif BENCHMARK == 0
#define M 7
#define K 5
#define N 9
#elif BENCHMARK == 1
#else
#endif

#define MIN -10
#define MAX 10

#define for2(VAR_ROW, VAR_COL, ROWS, COLS) \
	for (size_t VAR_ROW = 0; VAR_ROW < ROWS; ++VAR_ROW) \
	for (size_t VAR_COL = 0; VAR_COL < COLS; ++VAR_COL) 

Matrix createMatrix(const size_t rows, const size_t cols);
void destroyMatrix(Matrix *matrix);
void matrixSet(
		Matrix *matrix,
		const size_t row,
		const size_t col,
		const int value
	      );
int matrixGet(const Matrix matrix, const size_t row, const size_t col);
void generateRandomMatrix(
		Matrix *matrix,
		const int min,
		const int max
		);
void printMatrix(const Matrix matrix);
int matrixDotProduct(
		const Matrix matrixA,
		const Matrix matrixB,
		const size_t row,
		const size_t col
		);
Matrix matrixMultiplication(const Matrix matrixA, const Matrix matrixB);

#endif // !THREADS_MATRIX_H
