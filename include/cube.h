#ifndef CUBE_H
#define CUBE_H

// a struct representing a 3D cube
typedef struct cube {
    int vertices[8][3];
    int offset[2];
} cube;

// creates a new cube
cube cube_new(unsigned int size, int x_offset, int y_offset);

#endif // CUBE_H
