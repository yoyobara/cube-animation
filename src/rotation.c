#include <math.h>
#include "rotation.h"

#define a x_rotation
#define b y_rotation
#define c z_rotation

rotation_matrix rotation_matrix_new(float x_rotation, float y_rotation, float z_rotation) {

    rotation_matrix rot = {.data = {

        {cos(b) * cos(c), sin(a) * sin(b) * cos(c) - cos(a) * sin(c), cos(a) * sin(b) * cos(c) + sin(a) * sin(c)},
        {cos(b) * sin(c), sin(a) * sin(b) * sin(c) + cos(a) * cos(c), cos(a) * sin(b) * sin(c) - sin(a) * cos(c)},
        {-sin(b), sin(a) * cos(b), cos(a) * cos(b)}

    }};
    
    return rot;
}

// TODO try ChatGPT optimization to trig (not so important)
// rotation_matrix rotation_matrix_new(float x_rotation, float y_rotation, float z_rotation) {
//     float cos_b = cos(b);
//     float sin_b = sin(b);
//     float cos_a = cos(a);
//     float sin_a = sin(a);
//     float cos_c = cos(c);
//     float sin_c = sin(c);
//
//     float sin_a_sin_b = sin_a * sin_b;
//     float cos_a_sin_b = cos_a * sin_b;
//
//     rotation_matrix rot = {
//         .data = {
//             {cos_b * cos_c, sin_a_sin_b * cos_c - cos_a * sin_c, cos_a_sin_b * cos_c + sin_a * sin_c},
//             {cos_b * sin_c, sin_a_sin_b * sin_c + cos_a * cos_c, cos_a_sin_b * sin_c - sin_a * cos_c},
//             {-sin_b, sin_a * cos_b, cos_a * cos_b}
//         }
//     };
//     
//     return rot;
// }
