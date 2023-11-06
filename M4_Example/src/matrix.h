//
// Created by Tim Leys on 16/10/2023.
//

#ifndef UNTITLED1_MATRIX_H
#define UNTITLED1_MATRIX_H

#include "stdio.h"
#include "math.h"

struct point2d{
    float x, y;
};

struct point3d {
    float x, y, z;
};


struct matrix{
    float a00;
    float a01;
    float a02;

    float a10;
    float a11;
    float a12;

    float a20;
    float a21;
    float a22;
};

/// create a 2D point with given x, y coordinates.
struct point2d create_point2d(float x, float y);
/// create a 3D point with given x, y, z coordinates.
struct point3d create_point3d(float x, float y, float z);
/// create a matrix with only 0 values.
struct matrix create_matrix();
/// create a matrix that encodes the eye point transformation.
struct matrix create_eyepoint_matrix(float phi, float theta);
/// create a matrix that encodes a rotation along the z axis.
struct matrix create_rotz_matrix(float rad);

/// multiply a vector with matrix m.
struct point3d point_mult(struct point3d p, struct matrix m);

/// return the minimal value of a and b.
float min(float a, float b);
/// return the maximal value of a and b.
float max(float a, float b);




#endif //UNTITLED1_MATRIX_H
