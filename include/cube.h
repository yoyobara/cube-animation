#ifndef CUBE_H
#define CUBE_H

#define CUBE_SIZE 10

// a struct representing a 3D cube
typedef struct cube {
    int vertices[8][3];
} cube;

// creates a new cube
cube cube_new();

#endif // CUBE_H
