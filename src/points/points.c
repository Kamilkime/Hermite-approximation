#include <stdlib.h>
#include <stdio.h>

#include "points.h"

// Creates a new point and returns a pointer to it
struct Point *createPoint(long double x, long double y) {
    Point *point = (Point*) malloc(sizeof(Point));
    if (point == NULL) {
        printf("\nFAILED TO ALLOCATE POINT MEMORY!\n\n");
        exit(EXIT_FAILURE);
    }

    point -> x = x;
    point -> y = y;

    return point;
}

// Reads points from file and outputs them to the given list
void readPointsFromFile(FILE *pointsFile, List *pointsList) {
    long double tempX, tempY;

    while (fscanf(pointsFile, "%Lf %Lf", &tempX, &tempY) == 2) {
        addToList(pointsList, createPoint(tempX, tempY));
    }
}

// Sorts points in the given list (bubble sort with possible early termination)
void sortPoints(List *pointsList) {
    int last = pointsList -> items - 1, currentIndex;
    for (; last > 0; last--) {
        int changed = 0;

        for (currentIndex = 0; currentIndex < last; currentIndex++) {
            Point *currentPoint = (Point*) getFromList(pointsList, currentIndex);
            Point *nextPoint = (Point*) getFromList(pointsList, currentIndex + 1);

            if (currentPoint -> x > nextPoint -> x) {
                setInListByIndex(pointsList, currentIndex, nextPoint);
                setInListByIndex(pointsList, currentIndex + 1, currentPoint);

                changed = 1;
            }
        }

        if (!changed) {
            return;
        }
    }
}