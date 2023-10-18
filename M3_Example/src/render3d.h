//
// Created by Tim Leys on 14/10/2023.
//

#ifndef UNTITLED1_RENDER3D_H
#define UNTITLED1_RENDER3D_H

#include "math.h"
#include "matrix.h"

struct line{
    struct point2d from, to;
};

struct edge{
    struct point3d from, to;
};

struct sqr{
    struct edge edges[12];
};

struct sqr_2d{
    struct line lines[12];
};


/*///// STRUCT CONSTRUCTORS /////*/

/// create a line from point (x1, y1) to (x2, y2).
struct line create_line(float x1, float y1, float x2, float y2);

/// create an edge from point (x1, y1, z1) to (x2, y2, z2);
struct edge create_edge(float x1, float y1, float z1, float x2, float y2, float z2);
/// create a square around the origin.
struct sqr create_sqr();

/// projects 3d point to 2d point after eyepoint transformation.
struct point2d project(struct point3d p, float d);

/// returns polar coordinates of point p
void to_polar(struct point3d p, float *r, float *phi, float *theta);

/// rotate sqr according to given matrix
void transform(struct sqr *s, struct matrix m);

/// translate the sqr allong point d.
void translate(struct sqr *s, struct point3d d);

/// project square to 2D image.
struct sqr_2d flatten(struct sqr s);

/// center and stretch square to fit screen.
void center(struct sqr_2d *s);

#endif //UNTITLED1_RENDER3D_H
