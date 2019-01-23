all:
	@gcc -pedantic -Wall src/main.c src/gauss/*.c src/list/*.c src/matrix/*.c src/points/*.c src/spline/*.c -o approx -lm

clean: all
	@rm -f *.o

test: clean
	@printf "STARTING TESTS:\n"

	@mkdir -p test/1default # Create a folder for the first test
	@printf "\n"
	# First test - points from dane.1, default parameters
	./approx -s test/1default/spline -p test/dane.1 -g test/1default/plotfile

	@mkdir -p test/1,m=10 # Create a folder for the second test
	@printf "\n"
	# Second test - points from dane.1, max-polynomial = 10
	./approx -s test/1,m=10/spline -p test/dane.1 -g test/1,m=10/plotfile -m 10

	@mkdir -p test/1,m=10,d=10 # Create a folder for the third test
	@printf "\n"
	# Third test - points from dane.1, max-polynomial = 10, max-derivative = 10
	./approx -s test/1,m=10,d=10/spline -p test/dane.1 -g test/1,m=10,d=10/plotfile -m 10 -d 10

	@mkdir -p test/1,m=25,d=25 # Create a folder for the fourth test
	@printf "\n"
	# Fourth test - points from dane.1, max-polynomial = 25, max-derivative = 25
	./approx -s test/1,m=25,d=25/spline -p test/dane.1 -g test/1,m=25,d=25/plotfile -m 25 -d 25

	@mkdir -p test/1,m=4,d=3 # Create a folder for the fifth test
	@printf "\n"
	# Fifth test - points from dane.1, max-polynomial = 4, max-derivative = 3
	./approx -s test/1,m=4,d=3/spline -p test/dane.1 -g test/1,m=4,d=3/plotfile -m 4 -d 3

	@mkdir -p test/2default # Create a folder for the sixth test
	@printf "\n"
	# Sixth test - points from dane.2, default parameters
	./approx -s test/2default/spline -p test/dane.2 -g test/2default/plotfile

	@mkdir -p test/2,m=5 # Create a folder for the seventh test
	@printf "\n"
	# Seventh test - points from dane.2, max-polynomial = 5
	./approx -s test/2,m=5/spline -p test/dane.2 -g test/2,m=5/plotfile -m 5

	@mkdir -p test/2,m=5,d=2 # Create a folder for the eighth test
	@printf "\n"
	# Eighth test - points from dane.2, max-polynomial = 5, max-derivative = 2
	./approx -s test/2,m=5,d=2/spline -p test/dane.2 -g test/2,m=5,d=2/plotfile -m 5 -d 2

	@mkdir -p test/3default # Create a folder for the ninth test
	@printf "\n"
	# Ninth test - points from dane.3, default parameters
	./approx -s test/3default/spline -p test/dane.3 -g test/3default/plotfile

	@mkdir -p test/3,m=6,d=7 # Create a folder for the tenth test
	@printf "\n"
	# Tenth test - points from dane.3, max-polynomial = 6, max-derivative = 7
	./approx -s test/3,m=6,d=7/spline -p test/dane.3 -g test/3,m=6,d=7/plotfile -m 6 -d 7

	@mkdir -p test/4default # Create a folder for the eleventh test
	@printf "\n"
	# Eleventh test - points from dane.4, default parameters
	./approx -s test/4default/spline -p test/dane.4 -g test/4default/plotfile

	@mkdir -p test/5default # Create a folder for the twelfth test
	@printf "\n"
	# Twelfth test - points from dane.5, default parameters
	./approx -s test/5default/spline -p test/dane.5 -g test/5default/plotfile

	@printf "\n"