#ifndef _POINTS_H_IS_INCLUDED_
#define _POINTS_H_IS_INCLUDED_

#include <stdio.h>

#include "../list/list.h"

// A two-dimensional point
typedef struct Point {
    long double x;
    long double y;
} Point;

// Creates a new point and returns a pointer to it
struct Point *createPoint(long double x, long double y);

// Reads points from file and outputs them to the given list
void readPointsFromFile(FILE *pointsFile, List *pointsList);

// Sorts points in the given list
void sortPoints(List *pointsList);

#endif