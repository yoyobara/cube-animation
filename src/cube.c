#include "cube.h"

cube cube_new(unsigned int size, int x_offset, int y_offset) {

    cube c;

    // fill vertices
    int index_counter = 0;
    for (int i = -size ; i != 3 * size ; i += 2 * size)
        for (int j = -size ; j != 3 * size ; j += 2 * size)
            for (int k = -size ; k != 3 * size ; k += 2 * size) {
                c.vertices[index_counter][0] = i;
                c.vertices[index_counter][1] = j;
                c.vertices[index_counter][2] = k;
                index_counter++;
            }

    c.offset[0] = x_offset;
    c.offset[1] = y_offset;

    return c;
}
