#include "cube.h"

cube cube_new() {

    cube c;

    // fill vertices
    int index_counter = 0;
    for (int i = -CUBE_SIZE ; i != 3 * CUBE_SIZE ; i += 2 * CUBE_SIZE)
        for (int j = -CUBE_SIZE ; j != 3 * CUBE_SIZE ; j += 2 * CUBE_SIZE)
            for (int k = -CUBE_SIZE ; k != 3 * CUBE_SIZE ; k += 2 * CUBE_SIZE) {
                c.vertices[index_counter][0] = i;
                c.vertices[index_counter][1] = j;
                c.vertices[index_counter][2] = k;
                index_counter++;
            }

    return c;
}
