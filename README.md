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
* **max-polynomial** - max polynomial degree which will be used for calculations (the bigger - the better approximation but also longer calculation time), by default 20
* **max-derivative** - max derivative degree which will be used for calculations (the bigger - the better approximation but also longer calculation time), by default 20
* **points-file** - name of the file from which the base two-dimensional points will be read
* **gnuplot-file** - name of the file to which `n_points` generated approximation points will be written
* **from_x** - min point of approximation, by default x coordinate of the first point
* **to_x** - max point of approximation, by default x coordinate of the last point
* **n_points** - number of points to calculate, by default 1000

## Example
An example output files can be found in `test` directory

Example program usage commands can be found in `makefile`

## Example approximations visualised using gnuplot
![1,m=25,d=25](/gnuplot-examples/1,m=25,d=25.png)
**Command:** `./approx -s test/1,m=25,d=25/spline -p test/dane.1 -g test/1,m=25,d=25/plotfile -m 25 -d 25`


![2,m=5.png](/gnuplot-examples/2,m=5.png)
**Command:** `./approx -s test/2,m=5/spline -p test/dane.2 -g test/2,m=5/plotfile -m 5`


![3,m=6,d=7.png](/gnuplot-examples/3,m=6,d=7.png)
**Command:** `./approx -s test/3,m=6,d=7/spline -p test/dane.3 -g test/3,m=6,d=7/plotfile -m 6 -d 7`


![4default](/gnuplot-examples/4default.png)
**Command:** `./approx -s test/4default/spline -p test/dane.4 -g test/4default/plotfile`


## License
The analyser is licensed under **MIT License** - https://choosealicense.com/licenses/mit/
