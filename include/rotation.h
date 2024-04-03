#pragma once

typedef struct rotation_matrix {
    float data[3][3];

} rotation_matrix;

// creates a new rotation matrix from angles (rad)
rotation_matrix rotation_matrix_new(float x_rotation, float y_rotation, float z_rotation);
