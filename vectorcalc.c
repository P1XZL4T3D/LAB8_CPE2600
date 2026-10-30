/****************************************************************
*   FileName: vectorcalc.h
*   Authour: James F. Connelly
*   Date: 9/29/2026
*   Discription: Header file for vectorcalc.c, defines a struct for a vector and functions to perform vector calculations
****************************************************************/

#include "vector.h"
#include <stdio.h>
#include <string.h>


// Takes two vectors and returns their sum
Vector vector_add(Vector a, Vector b) {\
    Vector result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

// Takes two vectors and returns their difference
Vector vector_subtract(Vector a, Vector b) {
    Vector result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

//Returns the dot product of two vectors
float vector_dot(Vector a, Vector b) {
    float result;
    result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    return result;
}

// Returns the cross product of two vectors
Vector vector_cross(Vector a, Vector b) {
    Vector result;
    result.x = (a.y * b.z) - (a.z * b.y);
    result.y = (a.z * b.x) - (a.x * b.z);
    result.z = (a.x * b.y) - (a.y * b.x);
    return result;
}

//Takes a vector and a scalar and returns the scaled vector
Vector vector_scale(Vector a, float scalar) {
    Vector result;
    result.x = a.x * scalar;
    result.y = a.y * scalar;
    result.z = a.z * scalar;
    return result;
}