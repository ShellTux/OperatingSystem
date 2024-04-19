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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void generateRandomMatrix(
		Matrix *matrix,
		const int min,
		const int max
		)
{
	if (matrix == NULL || matrix->data == NULL) {
		return;
	}

	for2 (i, j, matrix->rows, matrix->cols) {
		matrixSet(matrix, i, j, rand() % (max - min) + min);
	}
}

void printMatrix(const Matrix matrix)
{
	if (matrix.data == NULL || matrix.rows == 0 || matrix.cols == 0) {
		return;
	}

	printf("[");
	for2 (i, j, matrix.rows, matrix.cols) {
		if (j == 0) {
			printf("\n  [");
		} else if (j != 0) {
			printf(", ");
		}

		printf("%4d", matrixGet(matrix, i, j));

		if (j == matrix.cols - 1) {
			printf("]");
			if (i == matrix.rows - 1) {
				printf("\n");
			}
		}
	}
	printf("]\n");
}

Matrix createMatrix(const size_t rows, const size_t cols)
{
	Matrix matrix = {
		.data = NULL,
		.rows = rows,
		.cols = cols,
	};

	const unsigned long elementSize = sizeof(matrix.data[0]);
	matrix.data = malloc(elementSize * matrix.rows * matrix.cols);

	return matrix;
}

void destroyMatrix(Matrix *matrix)
{
	if (matrix == NULL
			|| matrix->data == NULL
			|| matrix->rows == 0
			|| matrix->cols == 0
	   ) {
		return;
	}

	free(matrix->data);
}

void matrixSet(
		Matrix *matrix,
		const size_t row,
		const size_t col,
		const int value
	      )
{
	matrix->data[row * matrix->cols + col] = value;
}

int matrixGet(const Matrix matrix, const size_t row, const size_t col)
{
	return matrix.data[row * matrix.cols + col];
}

Matrix matrixMultiplication(const Matrix matrixA, const Matrix matrixB)
{
	Matrix matrixC = createMatrix(matrixA.rows, matrixB.cols);

	if (matrixA.data == NULL || matrixB.data == NULL) {
		return matrixC;
	}

	if (matrixA.cols != matrixB.rows) {
		fprintf(stderr,
				"Error: Number of columns in the first matrix "
				"must be equal to the number of rows in the "
				"second matrix for multiplication.\n");
		return matrixC;
	}

	for2 (i, j, matrixA.rows, matrixB.cols) {
		const int sum = matrixDotProduct(matrixA, matrixB, i, j);
		matrixSet(&matrixC, i, j, sum);
	}

	return matrixC;
}

int matrixDotProduct(
		const Matrix matrixA,
		const Matrix matrixB,
		const size_t row,
		const size_t col
		)
{
	int sum = 0;

	for (size_t k = 0 ; k < matrixA.cols ; ++k) {
		sum += matrixGet(matrixA, row, k) * matrixGet(matrixB, k, col);
	}

	return sum;
}
