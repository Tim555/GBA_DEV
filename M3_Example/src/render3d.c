//
// Created by Tim Leys on 14/10/2023.
//

#include "render3d.h"


struct line create_line(float x1, float y1, float x2, float y2){
    struct line l = {.from = create_point2d(x1, y1), .to = create_point2d(x2, y2)};
    return l;
}

struct edge create_edge(float x1, float y1, float z1,
                        float x2, float y2, float z2){
    struct edge e = {.from = create_point3d(x1, y1, z1),
                     .to= create_point3d(x2, y2, z2)};
    return e;
}

struct sqr create_sqr(){
    struct sqr out = {};
    // Front face
    out.edges[0] = create_edge(1, 1, 1, 1, -1, 1);
    out.edges[1] = create_edge(1, -1, 1, -1, -1, 1);
    out.edges[2] = create_edge(-1, -1, 1, -1, 1, 1);
    out.edges[3] = create_edge(-1, 1, 1, 1, 1, 1);

    // Back face
    out.edges[4] = create_edge(1, 1, -1, 1, -1, -1);
    out.edges[5] = create_edge(1, -1, -1, -1, -1, -1);
    out.edges[6] = create_edge(-1, -1, -1, -1, 1, -1);
    out.edges[7] = create_edge(-1, 1, -1, 1, 1, -1);

    // Connector edges
    out.edges[8] = create_edge(1, 1, 1, 1, 1, -1);
    out.edges[9] = create_edge(1, -1, 1, 1, -1, -1);
    out.edges[10] = create_edge(-1, 1, 1, -1, 1, -1);
    out.edges[11] = create_edge(-1, -1, 1, -1, -1, -1);

    return out;
}

struct point2d project(const struct point3d p, float d){
    struct point2d out = {.x = d * p.x / (-p.z), .y = d*p.y /(-p.z)};
    return out;
}

void to_polar(struct point3d p, float *r, float *phi, float *theta){
    (*r) = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
    (*theta) = atan2(p.y, p.x);
    (*phi) = acos(p.z / (*r));
}

void transform(struct sqr *s, struct matrix m){
    int ii;
    for(ii=0; ii < 12; ++ii){
        s->edges[ii].from = point_mult(s->edges[ii].from, m);
        s->edges[ii].to = point_mult(s->edges[ii].to, m);
    }
}

void translate(struct sqr *s, struct point3d d){
    int ii;
    for(ii=0; ii < 12; ++ii){
        s->edges[ii].from.x += d.x;
        s->edges[ii].from.y += d.y;
        s->edges[ii].from.z += d.z;

        s->edges[ii].to.x += d.x;
        s->edges[ii].to.y += d.y;
        s->edges[ii].to.z += d.z;
    }
}

struct sqr_2d flatten(struct sqr s){
    struct sqr_2d lines;
    int ii;
    for(ii=0; ii < 12; ++ii){
        struct point2d f = project(s.edges[ii].from, 1);
        struct point2d t = project(s.edges[ii].to, 1);
        struct line nl = {.from = f, .to = t};
        lines.lines[ii] = nl;
    }

    return lines;
}

void center(struct sqr_2d *s){
    int ii;
    float x_min, x_max, y_min, y_max, x_r, y_r, i_x, i_y, d;
    x_min = 10000;
    x_max = -10000;
    y_min = 10000;
    y_max = -10000;

    for(ii = 0; ii < 12; ++ii){
        x_min = min(x_min, s->lines->from.x);
        x_min = min(x_min, s->lines->to.x);
        x_max = max(x_max, s->lines->from.x);
        x_max = max(x_max, s->lines->to.x);
        y_min = min(y_min, s->lines->from.y);
        y_min = min(y_min, s->lines->to.y);
        y_max = max(y_max, s->lines->from.y);
        y_max = max(y_max, s->lines->to.y);
    }
    x_r = x_max - x_min;
    y_r = y_max - y_min;

    i_x = 60 * (x_r / max(x_r, y_r));
    i_y = 60 * (y_r / max(x_r, y_r));
    d   = i_x / x_r;

    printf("x_r: %f \n", x_r);
    printf("x_max: %f \n", x_max);
    printf("x_min: %f \n", x_min);
    printf("scaling factor: %f \n", d);


    for(ii = 0; ii < 12; ++ii){
        s->lines[ii].to.x =  s->lines[ii].to.x * d + 120;
        s->lines[ii].to.y =  s->lines[ii].to.y * d + 80;
        s->lines[ii].from.x =  s->lines[ii].from.x * d + 120;
        s->lines[ii].from.y =  s->lines[ii].from.y * d + 80;
    }
}