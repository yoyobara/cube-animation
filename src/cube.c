#include <math.h>
#include <stdio.h>
#include "cube.h"

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


// moves the cube
void cube_translate(cube* c, int x, int y) {
    c->offset[0] = x;
    c->offset[1] = y;
}

// scales a cube by a factor
void cube_scale(cube* c, float factor) {
    
    // multiply all coords by factor
    for (int i = 0 ; i < 24 ; i++) {
        c->vertices[i / 3][i % 3] *= factor;
    }
}

cube cube_new(float size_factor, int x_offset, int y_offset) {

    cube c;

    // fill vertices with normal coords
    int index_counter = 0;
    for (int i = -1 ; i != 3 ; i += 2)
        for (int j = -1 ; j != 3 ; j += 2)
            for (int k = -1 ; k != 3 ; k += 2) {
                c.vertices[index_counter][0] = i;
                c.vertices[index_counter][1] = j;
                c.vertices[index_counter][2] = k;
                index_counter++;
            }
    
    cube_scale(&c, size_factor);
    cube_translate(&c, x_offset, y_offset);

    return c;
}

// vertex points to x,y,z array
void rotate_vertex(float *vertex, float x_rotation, float y_rotation, float z_rotation) {
    float cosZrotation = cos(z_rotation);
    float sinZrotation = sin(z_rotation);

    float x = vertex[0], y = vertex[1];
    printf("%f %f\n", x, y);

    vertex[0] = x * cosZrotation + y * sinZrotation;
    vertex[1] = - x * sinZrotation + y * cosZrotation;
}

void cube_rotate(cube* c, float x_rotation, float y_rotation, float z_rotation) {
    for (int i = 0 ; i < 8 ; i++) {
        rotate_vertex(c->vertices[i], x_rotation, y_rotation, z_rotation);
    }
}

