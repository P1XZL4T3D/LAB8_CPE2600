Vector Calculator
Description
The Vector Calculator is a command-line program written in C that allows users to create and manipulate 3-dimensional vectors.
__________
The program supports:

Vector creation
Vector addition
Vector subtraction
Dot products
Cross products
Scalar multiplication
Saving vectors to CSV files
Loading vectors from CSV files
Vector storage uses dynamic memory so the program is not limited to storing only 10 vectors.
__________
Build Instructions
Build using gcc:

gcc main.c vector.c vectorcalc.c -o vectorcalc
Or if using a Makefile:

make
Running the Program
Run the program:
__________
./vectorcalc
Display help:

./vectorcalc -h
__________
Supported Commands
Create a Vector
a = 1 2 3

Display a Vector
a

List All Vectors
list

Add Vectors
c = a + b
or
a + b

Subtract Vectors
c = a - b

Dot Product
a . b

Cross Product
c = a x b

Scalar Multiplication
c = a * 2
or
c = 2 * a
__________
Save Vectors
save vectors.csv

Load Vectors
load vectors.csv

Clear Memory
clear

Exit
quit
__________
Dynamic Memory
The program stores vectors in a dynamically allocated array.

When vector storage becomes full, the array size is doubled using realloc().

Memory is released when:

The clear command is executed.
The program exits.
This allows the program to store a large number of vectors while avoiding memory leaks.
