#pragma once

// a struct representing a 3D cube
typedef struct cube {
    float vertices[8][3];
    int offset[2];
} cube;

// defined in cube.c
extern const int EDGES_INDEXES[12][2];

// creates a new cube
cube cube_new(float size_factor, int x_offset, int y_offset);

// set cube origin
void cube_translate(cube* c, int x, int y);
