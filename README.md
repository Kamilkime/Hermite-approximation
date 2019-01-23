# Hermite-approximation
Polynomial regression calculator using Hermite polynomials 

## About the topic
* [Least-squares function approximation](https://en.wikipedia.org/wiki/Least-squares_function_approximation)
* [Polynomial regression](https://en.wikipedia.org/wiki/Polynomial_regression)
* [Hermite polynomials](https://en.wikipedia.org/wiki/Hermite_polynomials)

## Purpose
The calculator was created as a part of **Programming languages and methodology** laboratories (Warsaw University of Technology, Electrical Faculty, Applied Computer Science, semester I)

## Building
`make clean`

## Usage
`./approx -s spline-file [-m max-polynomial] [-d max-derivative] [-p points-file] [ -g gnuplot-file [-f from_x -t to_x -n n_points ] ]`
* **spline-file** - name of the file to which the spline functions will be written if `points-file` was also given, otherwise the spline will be read from a given file
* **max-polynomial** - max polynomial degree which will be used for calculations (the bigger - the better approximation but also longer calculation time)
* **max-derivative** - max derivative degree which will be used for calculations (the bigger - the better approximation but also longer calculation time) 
* **points-file** - name of the file from which the base two-dimensional points will be read
* **gnuplot-file** - name of the file to which `n_points` generated approximation points will be written
* **from_x** - min point of approximation
* **to_x** - max point of approximation
* **n_points** - number of points to calculate

## Example
An example output files can be found in `test` directory

Example program usage commands can be found in `makefile`

## License
The analyser is licensed under **MIT License** - https://choosealicense.com/licenses/mit/
