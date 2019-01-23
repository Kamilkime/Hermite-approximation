#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

// Load matrix from file
Matrix *readFromFile(char *fileName) {
	FILE *inputFile = fopen(fileName, "r");
	if (inputFile == NULL) {
		fprintf(stderr, "Cannot open file %s\n", fileName);
		return NULL;
	}

	Matrix *matrix = NULL;
	int rows = 0, columns = 0;
	
	fscanf(inputFile, "%d %d", &rows, &columns);

	matrix = createMatrix(rows, columns);
	if (matrix == NULL) {
		fprintf(stderr, "Could not create %dx%d matrix from file %s\n", rows, columns, fileName);
		return NULL;
	}

	int indexR = 0, indexC = 0;
	for (indexR = 0; indexR < rows; indexR++) {
		for (indexC = 0; indexC < columns; indexC++) {
			fscanf(inputFile, "%Lf", &(matrix -> data[indexR][indexC]));
		}
	}

	fclose(inputFile);

	return matrix;
}

// Create new, empty matrix
Matrix *createMatrix(int rows, int columns) {
	if (rows <= 0 || columns <= 0) {
		return NULL;
	}

	Matrix *matrix = malloc(sizeof(Matrix));
	if (matrix == NULL) {
        printf("\nFAILED TO ALLOCATE MATRIX MEMORY!\n\n");
        exit(EXIT_FAILURE);
    }

	matrix -> rows = rows;
	matrix -> columns = columns;

	matrix -> data = malloc(sizeof(long double*) * rows);
	if (matrix == NULL) {
        printf("\nFAILED TO ALLOCATE MATRIX DATA MEMORY!\n\n");
        exit(EXIT_FAILURE);
    }

	int i = 0;
	for (; i < rows; i++) {
		matrix -> data[i] = malloc(sizeof(long double) * columns);

		if (matrix -> data[i] == NULL) {
        	printf("\nFAILED TO ALLOCATE MATRIX SUB-DATA MEMORY!\n\n");
        	exit(EXIT_FAILURE);
    	}
	}

	return matrix;
}

// Print matrix
void printToScreen(Matrix *matrix) {
	int row = 0, column = 0;

	printf("[ \n");
	for (row = 0; row < matrix -> rows; row++) {
		printf("  ");

		for (column = 0; column < matrix -> columns; column++) {
			printf("%Lf ", matrix -> data[row][column]);
		}

		printf("; \n");
	}
	printf("]\n");
}

// Free matrix memory
void freeMatrix(Matrix *matrix) {
	int i = 0;
	for (; i < matrix -> rows; i++) {
		free(matrix -> data[i]);
	}

	free(matrix -> data);
	free(matrix);
}