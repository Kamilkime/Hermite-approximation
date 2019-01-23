#ifndef _MATRIX_H_IS_INCLUDED_
#define _MATRIX_H_IS_INCLUDED_

typedef struct Matrix {
	int rows, columns;
	long double **data;
} Matrix;

Matrix *readFromFile(char *fileName);
Matrix *createMatrix(int rows, int columns);

void printToScreen(Matrix *matrix);
void freeMatrix(Matrix *matrix);

#endif