#ifndef _SPLINE_H_IS_INCLUDED_
#define _SPLINE_H_IS_INCLUDED_

#include "../list/list.h"

// A polynomial spline of given arguments and max derivative degree
typedef struct Spline {
    int argNum;
    int maxDerivative;

    long double *args;
    long double **functionValues;
} Spline;

// Allocate spline memory
Spline *allocateSpline(int argNum, int maxDerivative);

// Create a spline of given max derivative degree from given points, assuming max polynomial degree
Spline *makeSpline(List *points, int maxPolynomial, int maxDerivative);

// Read spline from file
Spline *readSpline(FILE *splineFile);

// Write spline to file
void writeSpline(Spline *spline, FILE *splineFile);

// Calculate spline value for the given x value
long double splineValue(Spline *spline, long double x);

// Calculate probabilists Hermite polynomial value of given polynomial degree, derivative degree and x value
long double probabilistsHermitePolynomialValue(int polynomialDegree, int derivativeDegree, long double x);

// Calculate physicists Hermite polynomial value of given polynomial degree, derivative degree and x value
long double physicistsHermitePolynomialValue(int polynomialDegree, int derivativeDegree, long double x);

// Factor a number
long factorial(long n);

#endif