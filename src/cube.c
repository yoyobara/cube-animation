#include "cube.h"

cube cube_new() {

    cube c;

    // fill vertices
    int index_counter = 0;
    for (int i = -1 ; i != 3 ; i += 2) 
        for (int j = -1 ; j != 3 ; j += 2)
            for (int k = -1 ; k != 3 ; k += 2) {
                c.vertices[index_counter][0] = i;
                c.vertices[index_counter][1] = j;
                c.vertices[index_counter][2] = k;
            }

    return c;
}
