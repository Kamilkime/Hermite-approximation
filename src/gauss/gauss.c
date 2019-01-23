#include <stdlib.h>
#include <stdio.h>

#include "gauss.h"

// Eliminates the matrix
// Returns 0 if matrix was eliminated correctly and 1 if there was division by zero
int eliminate(Matrix *matrix, Matrix *b) {
	long double **mData = matrix -> data;
	long double **bData = b -> data;

	int n = 0;
	for (; n < matrix -> columns; n++) {
		if (mData[n][n] == 0) {
			return 1;
		}
		
		int row = n + 1, column = n;
		for (; row < matrix -> rows; row++) {
			long double proportionFactor = mData[row][n] / mData[n][n];

			for (column = n; column < matrix -> columns; column++) {
				mData[row][column] -= proportionFactor * mData[n][column];
			}

			bData[row][0] -= proportionFactor * bData[n][0];
		}
	}

	return 0;
}

// Backward substitutes the matrix calculating x'es
void backsubst(Matrix *matrix, Matrix *x, Matrix *b) {
	long double **mData = matrix -> data;
	long double **xData = x -> data;
	long double **bData = b -> data;

	int n = (b -> rows) - 1;

	// Calculate last x value
	xData[n][0] = bData[n][0] / mData[n][n];

	int i = n - 1, j;
	for (; i >= 0; i--) {
		long double partialDifference = bData[i][0];
		for (j = n; j > i; j--) {
			partialDifference -= mData[i][j] * xData[j][0];
		}

		xData[i][0] = partialDifference / mData[i][i];
	}
}