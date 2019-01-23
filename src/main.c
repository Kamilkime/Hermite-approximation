#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "points/points.h"
#include "list/list.h"
#include "spline/spline.h"

char *usage =
"Usage: %s -s spline-file [-m max-polynomial] [-d max-derivative] [-p points-file] [ -g gnuplot-file [-f from_x -t to_x -n n_points ] ]\n"
"            - max-polynomial defaults to 20\n"
"            - max-derivative defaults to 20\n\n"
"            if points-file is given then\n"
"               reads discrete 2D points from points-file\n"
"               writes spline approximation to spline-file\n"
"               - number of points should be >= 4\n"
"            else (points-file not given)\n"
"               reads spline from spline-file\n"
"            endif\n\n"
"            if gnuplot-file is given then\n"
"               makes table of n_points within <from_x,to_x> range\n"
"               - from_x defaults to x-coordinate of the first point in points-file,\n"
"               - to_x defaults to x-coordinate of the last point\n"
"               - n_points defaults to 1000\n"
"               - n_points must be > 1\n"
"            endif\n";

int main(int argc, char **argv) {

    // Last read option 
    int currentOption;

    // Name of the point input file
    char *pointsFileName;

    // Name of the spline file
    char *splineFileName;

    // Name of the gnuplot output file
    char *gnuplotFileName;

    // Max degree of calculated polynomial
    int maxPolynomial = 20;

    // Max degree of calculated derivative
    int maxDerivative = 20;

    // Range (double inclusive) for the generated points
    long double fromX = 0;
    long double toX = 0;

    // Number of points to generate
    int n = 1000;

    // Points list pointer
    List *points = initList(10);

    // Empty (for now) spline pointer
    Spline *spline = NULL;

    while ((currentOption = getopt(argc, argv, "s:p:g:f:t:n:m:d:")) != -1) {
        switch (currentOption) {
            case 'p':
                pointsFileName = optarg;
                break;
            case 's':
                splineFileName = optarg;
                break;
            case 'g':
                gnuplotFileName = optarg;
                break;
            case 'f':
                fromX = strtold(optarg, NULL);
                break;
            case 't':
                toX = strtold(optarg, NULL);
                break;
            case 'n':
                n = atoi(optarg);
                break;
            case 'm':
                maxPolynomial = atoi(optarg);
                break;
            case 'd':
                maxDerivative = atoi(optarg);
                break;  
            default:
                fprintf (stderr, usage, argv[0]);
                exit (EXIT_FAILURE);
        }
    }

    // Check if all given parameters are valid (if all are of syntax '-param paramValue')
    if(optind < argc) {
        fprintf(stderr, "\nBad parameters!\n");
        for(; optind < argc; optind++) {
            fprintf(stderr, "\t\"%s\"\n", argv[optind]);
        }

        fprintf(stderr, "\n");
        fprintf(stderr, usage, argv[0]);
        exit(EXIT_FAILURE);
    }

    if (maxPolynomial < 0) {
        fprintf (stderr, "%s: max-polynomial must be at least 0\n\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    if (maxDerivative < 0) {
        fprintf (stderr, "%s: max-derivative must be at least 0\n\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    // Points file given - read points, generate spline and save it
    if (pointsFileName != NULL) {

        // Open points file
        FILE *pointsFile = fopen(pointsFileName, "r");
        if (pointsFile == NULL) {
            fprintf (stderr, "%s: can not read points file: %s\n\n", argv[0], pointsFileName);
            exit (EXIT_FAILURE);
        }

        // Read points from file
        readPointsFromFile(pointsFile, points);

        // Close points file
        fclose(pointsFile);

        // Sort loaded points (by x, non-descending)
        sortPoints(points);

        // Open spline file
        FILE *splineFile = fopen(splineFileName, "w");
        if (splineFile == NULL) {
            fprintf (stderr, "%s: can not write spline file: %s\n\n", argv[0], splineFileName);
            exit (EXIT_FAILURE);
        }

        // Make a spline and write it to the file
        spline = makeSpline(points, maxPolynomial + 1, maxDerivative + 1);
        if (spline -> argNum > 0) {
            writeSpline(spline, splineFile);
        }

        fclose(splineFile);
    }
    
    // Point file not given - read spline from file
    else if (splineFileName != NULL) {
        FILE *splineFile = fopen(splineFileName, "r");
        if (splineFile == NULL) {
            fprintf (stderr, "%s: can not read spline file: %s\n\n", argv[0], splineFileName);
            exit (EXIT_FAILURE);
        }

        // Read a spline from the file
        spline = readSpline(splineFile);
        if (spline == NULL) {
            fprintf (stderr, "%s: bad contents of spline file: %s\n\n", argv[0], splineFileName);
            exit (EXIT_FAILURE);
        }
    }
    
    // No files given, exit
    else {
        fprintf (stderr, usage, argv[0]);
        exit (EXIT_FAILURE);
    }

    // Check spline size
    if (spline -> argNum < 1) {
        fprintf (stderr, "%s: bad spline: n=%d\n\n", argv[0], spline -> argNum);
        exit (EXIT_FAILURE);
    }

    // If gnuplot output file name given - generate it
    if (gnuplotFileName != NULL && n > 1) {
        FILE *gnuplotFile = fopen(gnuplotFileName, "w");
        if (gnuplotFile == NULL) {
            fprintf (stderr, "%s: can not write gnuplot file: %s\n\n", argv[0], gnuplotFileName);
            exit (EXIT_FAILURE);
        }

        // Range is not given - take it from points, spline or predefined values
        if (fromX == 0 && toX == 0) {
            if (points -> items > 1) {
                fromX = ((Point*) getFromList(points, 0)) -> x;
                toX = ((Point*) getFromList(points, points -> items - 1)) -> x;
            } else if (spline -> argNum > 1) {
                fromX = spline -> args[0];
                toX = spline -> args[spline -> argNum - 1];
            } else {
                fromX = 0.0;
                toX = 1.0;
            }
        }

        long double dx = (toX - fromX) / (n - 1);

        int i = 0;
        for (; i < n; i++) {
            fprintf(gnuplotFile, "%Lf %Lf\n", fromX + i * dx, splineValue(spline, fromX + i * dx));
        }

        fclose(gnuplotFile);
    }

    return 0;
}