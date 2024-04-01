#ifndef CUBE_H
#define CUBE_H

// a struct representing a 3D cube
typedef struct cube {
    int vertices[8][3];
    int offset[2];
} cube;

const int EDGES_INDEXES[12][2] = {
        {0, 1},
        {0, 2},
        {0, 4},
        {1, 3},
        {1, 5},
        {2, 3},
        {2, 6},
        {3, 7},
        {4, 5},
        {4, 6},
        {5, 7},
        {6, 7}
};

// creates a new cube
cube cube_new(unsigned int size, int x_offset, int y_offset);

#endif // CUBE_H
