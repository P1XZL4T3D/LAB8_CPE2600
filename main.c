/****************************************************************
*   FileName: main.c
*   Authour: James F. Connelly
*   Date: 9/29/2026
*   Discription: Main function for testing vector calculations
****************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "vectorcalc.h"

int main(int argc, char *argv[]) {

    
    char input[1000]; // Buffer for user input
    

    Vector *vector_memory = NULL; // Array to hold up to 10 vectors

    static int vector_count = 0; 
    int capacity = 0;

    bool running = true; // Flag to control the main loop

    //if args has -h print out a help message
    if(argc > 1 && strcmp(argv[1], "-h") == 0) {
        printf("Welcome to the vector calculator!\n");
        printf("You can create vectors, perform operations on them, and display them.\n");
        printf("Command List:\n");
        printf("  <name> = <x> <y> <z> : Create a vector with the given name and components\n");
        printf("  <name> + <name> : Add two vectors and display the result\n");
        printf("  <name> - <name> : Subtract two vectors and display the result\n");
        printf("  <name> . <name> : Dot product of two vectors and display the result\n");
        printf("  <name> x <name> : Cross product of two vectors and display the result\n");
        printf("  <name> * <scalar> : Scale a vector by a scalar and display the result\n");
        printf("  list : List all created vectors\n");
        printf("  clear : Clear all created vectors\n");
        printf("  quit : Exit the program\n\n");
    }

    while(running) { //Running Loop for the calulator
    
        //prompt user for input
        printf("minimat> ");
        fgets(input, sizeof(input), stdin);
        //Used for parsing input regarding vector creation
        char name[100];
        double x, y, z;

        //Used for parsing input regarding vector operations
        char resultName[100];
        char leftName[100];
        char rightName[100];
        char filename[250];

        // Remove newline
        input[strcspn(input, "\n")] = '\0';
        
        //remove commas, cuz I don't want to deal with them honestly
        for(int i = 0; input[i]; i++) {
            if(input[i] == ',') {
                input[i] = ' ';
            }
        }
        
        //Command parsing logic
        if(strcmp(input, "quit") == 0) { //Quit command
            running = false;
            fprintf(stderr, "Exiting...\n");
        } else if(strcmp(input, "list") == 0) { //List Command
            list_vectors(vector_memory, vector_count);
        } else if(strcmp(input, "clear") == 0) { // Clear command
               free(vector_memory);

                vector_memory = NULL;
                vector_count = 0;   
                capacity = 0;
        } else if(sscanf(input, "load %255s", filename) == 1){
            load_vectors(filename,  &vector_memory, &vector_count, &capacity);
        } else if(sscanf(input, "save %255s", filename) == 1) {
            save_vectors(filename, vector_memory, vector_count);
        } else if(sscanf(input, "%s = %lf %lf %lf", name, &x, &y, &z) == 4) { //Vector creation command
                Vector v = create_vector(name, x, y, z);
                add_vector(&vector_memory, &vector_count, &capacity, v);

                display(v);
                continue;
        } else if(sscanf(input, "%s = %s + %s", resultName, leftName, rightName) == 3) { //Vector addition and assignment command
            int leftIndex = find_vector(vector_memory, vector_count, leftName); //Finds left vector in vector_memory

            int rightIndex = find_vector(vector_memory, vector_count, rightName);

            if(leftIndex == -1 || rightIndex == -1) {
                printf("Error: Vector not found.\n");
            } else {

                Vector result = vector_add(vector_memory[leftIndex], vector_memory[rightIndex]);

                strcpy(result.name, resultName);

                add_vector(&vector_memory, &vector_count, &capacity, result);

                display(result);
            }
        } else if(sscanf(input, "%s + %s", leftName, rightName) == 2) { //Vector addition command without assignment
            int leftIndex = find_vector(vector_memory, vector_count, leftName);

            int rightIndex = find_vector(vector_memory, vector_count, rightName);

            if(leftIndex == -1 || rightIndex == -1) {
                printf("Error: Vector not found.\n");
            } else {
                Vector result = vector_add(vector_memory[leftIndex], vector_memory[rightIndex]);
                
                strcpy(result.name, "ans");

                display(result);
            }
        } else if(sscanf(input, "%s = %s - %s", resultName, leftName, rightName) == 3) { //Vector subtraction and assignment command
            int leftIndex = find_vector(vector_memory, vector_count, leftName); //Finds left vector in vector_memory

            int rightIndex = find_vector(vector_memory, vector_count, rightName);

            if(leftIndex == -1 || rightIndex == -1) {
                printf("Error: Vector not found.\n");
            } else {
                Vector result = vector_subtract(vector_memory[leftIndex], vector_memory[rightIndex]);

                strcpy(result.name, resultName);

                add_vector(&vector_memory, &vector_count, &capacity, result);
                display(result);
            }
        } else if(sscanf(input, "%s - %s", leftName, rightName) == 2) { //Vector subtraction command without assignment
            int leftIndex = find_vector(vector_memory, vector_count, leftName);

            int rightIndex = find_vector(vector_memory, vector_count, rightName);

            if(leftIndex == -1 || rightIndex == -1) {
                printf("Error: Vector not found.\n");
            } else {
                Vector result = vector_subtract(vector_memory[leftIndex], vector_memory[rightIndex]);
                
                strcpy(result.name, "ans");

                display(result);
            }
        } else if(sscanf(input, "%s . %s", leftName, rightName) == 2) { //Dot product command
            int leftIndex = find_vector(vector_memory, vector_count, leftName);

            int rightIndex = find_vector(vector_memory, vector_count, rightName);

            if(leftIndex == -1 || rightIndex == -1) {
                printf("Error: Vector not found.\n");
            } else {
                float result = vector_dot(vector_memory[leftIndex], vector_memory[rightIndex]);

                printf("ans = %.2f\n", result);
            }
        } else if(sscanf(input, "%s = %s x %s", resultName, leftName, rightName) == 3) { //Cross product and assignment command
            int leftIndex = find_vector(vector_memory, vector_count, leftName);

            int rightIndex = find_vector(vector_memory, vector_count, rightName);

            if(leftIndex == -1 || rightIndex == -1) {
                printf("Error: Vector not found.\n");
            } else {
                Vector result = vector_cross(vector_memory[leftIndex], vector_memory[rightIndex]);

                strcpy(result.name, resultName);

                add_vector(&vector_memory, &vector_count, &capacity, result);
                display(result);
            }
        } else if(sscanf(input, "%s x %s", leftName, rightName) == 2) { //Cross product command without assignment
            int leftIndex = find_vector(vector_memory, vector_count, leftName);

            int rightIndex = find_vector(vector_memory, vector_count, rightName);

            if(leftIndex == -1 || rightIndex == -1) {
                printf("Error: Vector not found.\n");
            } else {
                Vector result = vector_cross(vector_memory[leftIndex], vector_memory[rightIndex]);
                strcpy(result.name, "ans");
                display(result);
            }
        } else if(sscanf(input, "%s = %s * %lf", resultName, leftName, &x) == 3 || sscanf(input, "%s = %lf * %s", resultName, &x, rightName) == 3) { //Vector scaling and assignment command
            int indexleft = find_vector(vector_memory, vector_count, leftName);
            int indexright = find_vector(vector_memory, vector_count, rightName);

            if(indexleft == -1 && indexright == -1) {
                printf("Error: Vector not found.\n");
            } else {

                int index;
                if (indexleft != -1){
                    index = indexleft;
                } else if (indexright != -1) {
                    index = indexright;
                }


                Vector result = vector_scale(vector_memory[index], x);

                strcpy(result.name, resultName);

                add_vector(&vector_memory, &vector_count, &capacity, result);

                display(result);
            }
        } else if(sscanf(input, "%s * %lf", leftName, &x) == 2 || sscanf(input, "%lf * %s", &x, rightName) == 2) { //Vector scaling command without assignment
            int indexleft = find_vector(vector_memory, vector_count, leftName);
            int indexright = find_vector(vector_memory, vector_count, rightName);
            
            if(indexleft == -1 && indexright == -1) {
                printf("Error: Vector not found.\n");
            } else {

                int index;

                if (indexleft != -1){
                    index = indexleft;
                } else if (indexright != -1) {
                    index = indexright;
                }

                Vector result = vector_scale(vector_memory[index], x);

                strcpy(result.name, "ans");
            
                display(result);
            }
        } else if(sscanf(input, "%s", name) == 1) { //Vector display command
            int index = find_vector(vector_memory, vector_count, name);
            if(index == -1) {
                printf("Invalid vector name or Operation.\n");
            } else {
                display(vector_memory[index]);
            }
        }
    }

    //Exit and free memory
    free(vector_memory);
    return 0;
}

//Creates a vector with the given name and components
Vector create_vector(char name[], float x, float y, float z) {
    Vector v;

    strcpy(v.name, name);
    v.x = x;
    v.y = y;
    v.z = z;

    return v;
} 

//Lists all vectors in the vector_memory array
void list_vectors(Vector *vector_memory, int size) {
    for(int i = 0; i < size; i++) {
        display(vector_memory[i]);
    }
} 

//Returns the index of the vector with the given name, or -1 if not found
int find_vector(Vector *vector_memory, int size, char *name) {
    for(int i = 0; i < size; i++) {
        if(strcmp(vector_memory[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

void add_vector(Vector **vector_memory, int *size, int *capacity, Vector v){
    int index = find_vector(*vector_memory, *size, v.name);

    if(index != -1) {
        (*vector_memory)[index] = v;
        return;
    }

    if(*size >= *capacity) {
        if(*capacity == 0) {
            *capacity = 10;
        } else {
            *capacity *= 2;
        } 


        *vector_memory = realloc(*vector_memory, *capacity * sizeof(Vector));

        if(*vector_memory == NULL) {
            printf("Out of memory.\n");
            exit(1);
        }
    }

    (*vector_memory)[*size] = v;
    (*size)++;
}

void display(Vector a) {
    printf("Vector %s = <%f, %f, %f>\n", 
        a.name, 
        a.x, 
        a.y, 
        a.z);
}

void load_vectors(char *filename, Vector **vector_memory, int *vector_count, int *capacity) { 
    FILE *fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("Could not open file.\n");
        return;
    }

    char name[100];
    float x;
    float y;
    float z;

    while(fscanf(fp, " %99[^,],%f,%f,%f", name, &x, &y, &z) == 4) {
        Vector v = create_vector(name, x, y, z);

        add_vector(vector_memory, vector_count, capacity, v);
    }

    fclose(fp);
}

void save_vectors(char *filename, Vector *vector_memory, int vector_count){ 
    FILE *fp = fopen(filename, "w");

    if(fp == NULL) {
        printf("Could not open file for writing.\n");
        return;
    }

    for(int i = 0; i < vector_count; i++) {
        fprintf(fp,
                "%s,%f,%f,%f\n",
                vector_memory[i].name,
                vector_memory[i].x,
                vector_memory[i].y,
                vector_memory[i].z);
    }

    fclose(fp);

    printf("%d vectors saved.\n", vector_count);
}