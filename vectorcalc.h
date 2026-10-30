/****************************************************************
*   FileName: vectorcalc.h
*   Authour: James F. Connelly
*   Date: 9/29/2026
*   Discription: Header file for vectorcalc.c, defines a struct for a vector and functions to perform vector calculations
****************************************************************/

#include "vector.h"

Vector vector_add(Vector a, Vector b);

Vector vector_subtract(Vector a, Vector b);

float vector_dot(Vector a, Vector b);

Vector vector_cross(Vector a, Vector b);

Vector vector_scale(Vector a, float scalar);
