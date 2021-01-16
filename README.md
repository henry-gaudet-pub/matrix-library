### Contact
Henry Gaudet
henrygaudet88@gmail.com

### Overview
I have prepared the following matrix library for consideration based on the following prompt:

<i>You’ve been tasked with writing a high-performance,
portable linear algebra library for a client who has
an awful case of not-invented-here syndrome.
This means you must only use standard libraries
(and miss out on the decades of optimizations in various BLAS implementations).
As a start, the client has asked for just transpose and multiplication of MxN matrices.
You should demonstrate the correctness of your solution.
Your solution should be well-documented so that it can be
used and maintained by the client’s engineering staff.
You are free to choose the underlying matrix representation and interface.
C++
Your solution should be implemented in standard C++11 (g++ or clang++ on Linux).
To keep things simple, the library may be header-only.
You may include a Makefile/CMakeLists.txt, or you may specify the compiler
command used to compile your source file:
g++ main.cpp -std=c++11 -lthread</i>

There are two files: `matrix.h` containing the libarary, and `main.cpp` containing unit tests for the `transpose()` and `multiply()` functions. The code is documented using the doxygen format so that it can be generated in html form.

### Building
`make`

### Running
`./matrix_test`

### Generating documentation
If doxygen is not installed:
`sudo apt install doxygen` or `sudo yum install doxygen`

Then to generate the docuementation:
`doxygen matrix.h`
