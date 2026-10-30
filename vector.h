/****************************************************************
*   FileName: vector.h
*   Authour: James F. Connelly
*   Date: 9/29/2026
*   Discription: Header file for vector.c, defines a struct for a vector
****************************************************************/ 

typedef struct Vector {
    char name[100];
    float x;
    float y;
    float z;
} Vector; 

Vector create_vector(char name[], float x, float y, float z);

void list_vectors(Vector *vector_memory, int size);

int find_vector(Vector *vector_memory, int size, char *name);

void add_vector(Vector **vector_memory, int *size, int *capacity, Vector v);

void display(Vector a);

void load_vectors(char *filename, Vector **vector_memory, int *vector_count, int *capacity);

void save_vectors(char *filename, Vector *vector_memory, int vector_count);

