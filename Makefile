all: matrix.h main.cpp
	g++ -std=c++11  matrix.h main.cpp -o matrix_test

clean:
	rm matrix_test