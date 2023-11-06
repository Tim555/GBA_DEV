//
// Created by Tim Leys on 16/10/2023.
//

#include "matrix.h"

struct point2d create_point2d(float x, float y){
    struct point2d p = {.x = x, .y = y};
    return p;
}

struct point3d create_point3d(float x, float y, float z){
    struct point3d p = {.x = x, .y = y, .z = z};
    return p;
}

struct matrix create_matrix(){
    struct matrix m;
    m.a00 = 0;
    m.a01 = 0;
    m.a02 = 0;

    m.a10 = 0;
    m.a11 = 0;
    m.a12 = 0;

    m.a20 = 0;
    m.a21 = 0;
    m.a22 = 0;
    return m;
}

struct matrix create_eyepoint_matrix(float phi, float theta){
    struct matrix m;
    m.a00 = -sin(theta);
    m.a01 = -cos(theta) * cos(phi);
    m.a02 = cos(theta) * sin(phi);

    m.a10 = cos(theta);
    m.a11 = -sin(theta) * cos(phi);
    m.a12 = sin(theta) * sin(phi);

    m.a20 = 0;
    m.a21 = sin(phi);
    m.a22 = cos(phi);
    return m;
}

struct matrix create_rotz_matrix(float rad){
    struct matrix m;
    m.a00 = cos(rad);
    m.a01 = sin(rad);
    m.a02 = 0;

    m.a10 = -sin(rad);
    m.a11 = cos(rad);
    m.a12 = 0;

    m.a20 = 0;
    m.a21 = 0;
    m.a22 = 1;
    return m;
}

struct point3d point_mult(struct point3d p, struct matrix m){
    float x = p.x * m.a00 + p.y * m.a10 + p.z * m.a20;
    float y = p.x * m.a01 + p.y * m.a11 + p.z * m.a21;
    float z = p.x * m.a02 + p.y * m.a12 + p.z * m.a22;

    return create_point3d(x, y, z);
}

float min(float a, float b){
    if (a < b){return a;} else {return b;}
}

float max(float a, float b){
    if (a > b){return a;} else {return b;}
}