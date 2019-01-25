#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "spline.h"
#include "../matrix/matrix.h"
#include "../points/points.h"
#include "../gauss/gauss.h"

// Allocate spline memory
Spline *allocateSpline(int argNum, int maxDerivative) {
    Spline *spline = (Spline*) malloc(sizeof(Spline));
    if (spline == NULL) {
        printf("\nFAILED TO ALLOCATE SPLINE MEMORY!\n\n");
        exit(EXIT_FAILURE);
    }

    spline -> argNum = argNum;
    spline -> maxDerivative = maxDerivative;

    spline -> args = (long double*) malloc(sizeof(long double) * argNum);
    if (spline -> args == NULL) {
        printf("\nFAILED TO ALLOCATE SPLINE ARGS MEMORY!\n\n");
        exit(EXIT_FAILURE);
    }

    spline -> functionValues = (long double**) malloc(sizeof(long double*) * argNum);
    if (spline -> functionValues == NULL) {
        printf("\nFAILED TO ALLOCATE SPLINE FUNCTION VALUES MEMORY!\n\n");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    for (; i < argNum; i++) {
        spline -> functionValues[i] = (long double*) calloc(maxDerivative, sizeof(long double));

        if (spline -> functionValues[i] == NULL) {
            printf("\nFAILED TO ALLOCATE SPLINE FUNCTION SUB-VALUES MEMORY!\n\n");
            exit(EXIT_FAILURE);
        }
    }

    return spline;
}

// Create a spline of given max derivative degree from given points, assuming max polynomial degree
Spline *makeSpline(List *points, int maxPolynomial, int maxDerivative) {

    // Main matrix size
    int rows = maxPolynomial, columns = maxPolynomial;

    // Main matrix for coefficient calculations
    Matrix *coefficientMatrix = createMatrix(rows, columns);

    // Constant matrix
    Matrix *constantMatrix = createMatrix(rows, 1);

    int r, c;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < columns; c++) {
            long double derivativeValue = 0.0;
            int i = 0;

            // Calculate partial derivatives
            for (; i < points -> items; i++) {
                long double x = ((Point*) getFromList(points, i)) -> x;
                derivativeValue += 2.0 * probabilistsHermitePolynomialValue(r, 0, x) * probabilistsHermitePolynomialValue(c, 0, x);
            }

            (coefficientMatrix -> data)[r][c] = derivativeValue;
        }
    }

    for (r = 0; r < rows; r++) {
        long double derivativeValue = 0.0;
        int i = 0;

        // Calculate partial derivatives
        for (; i < points -> items; i++) {
            long double x = ((Point*) getFromList(points, i)) -> x;
            long double y = ((Point*) getFromList(points, i)) -> y;

            derivativeValue += 2.0 * probabilistsHermitePolynomialValue(r, 0, x) * y;
        }

        (constantMatrix -> data)[r][0] = derivativeValue;
    }

    // Eliminate given matrixes
    if (eliminate(coefficientMatrix, constantMatrix)) {
        printf("\nDIVISION BY ZERO WHILE CALCULATING THE MATRIX, TERMINATING!\n\n");
        exit(EXIT_FAILURE);
    }

    // Result matrix
    Matrix *resultMatrix = createMatrix(rows, 1);
    backsubst(coefficientMatrix, resultMatrix, constantMatrix);

    // Create a spline
    int argNum = fmax(points -> items + 2, 11);

    long double fromX = ((Point*) getFromList(points, 0)) -> x;
    long double toX = ((Point*) getFromList(points, points -> items - 1)) -> x;

    long double step = (toX - fromX) / (argNum - 3);
    long double currentX = fromX - step;

    Spline *spline = allocateSpline(argNum, maxDerivative);
    for (r = 0; r < argNum; r++) {
        spline -> args[r] = currentX;

        for (c = 0; c < rows; c++) {
            int derivative = 0;

            // Generate spline function values from derivatives
            for (; derivative < maxDerivative; derivative++) {
                spline -> functionValues[r][derivative] += resultMatrix -> data[c][0] * probabilistsHermitePolynomialValue(c, derivative, currentX);
            }
        }

        currentX += step;
    }

    // Free memory
    freeMatrix(coefficientMatrix);
    freeMatrix(constantMatrix);
    freeMatrix(resultMatrix);

    return spline;
}

// Read spline from file
Spline *readSpline(FILE *splineFile) {
    int argNum, maxDerivative, arg, derivative;
    if (fscanf(splineFile, "%d", &argNum) != 1 || argNum < 1) {
        return NULL;
    }

    if (fscanf(splineFile, "%d", &maxDerivative) != 1 || maxDerivative < 0) {
        return NULL;
    }

    maxDerivative += 1;

    Spline *spline = allocateSpline(argNum, maxDerivative);
    for (arg = 0; arg < argNum; arg++) {
        if (fscanf(splineFile, "%Lf", &(spline -> args[arg])) != 1) {
            return NULL;
        }

        for (derivative = 0; derivative < maxDerivative; derivative++) {
            if (fscanf(splineFile, "%Lf", &(spline -> functionValues[arg][derivative])) != 1) {
                return NULL;
            }
        }
    }

    return spline;
}

// Write spline to file
void writeSpline(Spline *spline, FILE *splineFile) {
    fprintf(splineFile, "%d %d\n", spline -> argNum, spline -> maxDerivative - 1);

    int arg = 0, derivative;
    for (; arg < spline -> argNum; arg++) {
        fprintf(splineFile, "%Lf", spline -> args[arg]);
        for (derivative = 0; derivative < spline -> maxDerivative; derivative++) {
            fprintf(splineFile, " %Lf", spline -> functionValues[arg][derivative]);
        }

        fprintf(splineFile, "\n");
    }
}

// Calculate spline value for the given x value
long double splineValue(Spline *spline, long double x) {
    int i = spline -> argNum - 1, derivative = 0;
    for (; i > 0; i--) {
        if (spline -> args[i] <= x) {
            break;
        }
    }

    long double dx = x - spline -> args[i];
    long double splineValue = 0.0;

    // Sum derivatives
    for (; derivative < spline -> maxDerivative; derivative++) {
        splineValue += powl(dx, derivative) / factorial(derivative) * spline -> functionValues[i][derivative];
    }

    return splineValue;
}

// Calculate probabilists Hermite polynomial value of given polynomial degree, derivative degree and x value
long double probabilistsHermitePolynomialValue(int polynomialDegree, int derivativeDegree, long double x) {
    if (polynomialDegree == 0) {
        return (derivativeDegree == 0 ? 1.0 : 0.0);
    } else {
        if (derivativeDegree == 0) {
            long double prevValue = probabilistsHermitePolynomialValue(polynomialDegree - 1, 0, x);
            long double prevValueDerivative = probabilistsHermitePolynomialValue(polynomialDegree - 1, 1, x);

            return x * prevValue - prevValueDerivative;
        } else {
            return polynomialDegree * probabilistsHermitePolynomialValue(polynomialDegree - 1, derivativeDegree - 1, x);
        }
    }
}

// Calculate physicists Hermite polynomial value of given polynomial degree, derivative degree and x value
long double physicistsHermitePolynomialValue(int polynomialDegree, int derivativeDegree, long double x) {
    if (polynomialDegree == 0) {
        return (derivativeDegree == 0 ? 1.0 : 0.0);
    } else {
        if (derivativeDegree == 0) {
            long double prevValue = physicistsHermitePolynomialValue(polynomialDegree - 1, 0, x);
            long double prevValueDerivative = physicistsHermitePolynomialValue(polynomialDegree - 1, 1, x);

            return 2.0 * x * prevValue - prevValueDerivative;
        } else {
            return 2.0 * polynomialDegree * physicistsHermitePolynomialValue(polynomialDegree - 1, derivativeDegree - 1, x);
        }
    }
}

// Factor a number
long factorial(long n) {
    return n == 0 ? 1 : n * factorial(n - 1);
}
