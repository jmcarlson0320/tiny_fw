#include "tiny-fw.h"
#include <math.h>

vec2 new_vec2(float x, float y)
{
    vec2 v = {{x, y}};
    return v;
}

vec2 vec2_unit_vec(float angle)
{
    return new_vec2(cos(angle), sin(angle));
}

void vec2_add(vec2 *dest, const vec2 *u, const vec2 *v)
{
    dest->e[0] = u->e[0] + v->e[0];
    dest->e[1] = u->e[1] + v->e[1];
}

void vec2_sub(vec2 *dest, const vec2 *u, const vec2 *v)
{
    dest->e[0] = u->e[0] - v->e[0];
    dest->e[1] = u->e[1] - v->e[1];
}

void vec2_mult(vec2 *dest, const vec2 *v, float s)
{
    dest->e[0] = v->e[0] * s;
    dest->e[1] = v->e[1] * s;
}

void vec2_div(vec2 *dest, const vec2 *v, float s)
{
    dest->e[0] = v->e[0] / s;
    dest->e[1] = v->e[1] / s;
}

float vec2_dot(const vec2 *u, const vec2 *v)
{
    return u->e[0] * v->e[0] +
           u->e[1] * v->e[1];
}

float vec2_len_sqr(const vec2 *v)
{
    return v->e[0] * v->e[0] +
           v->e[1] * v->e[1];
}

float vec2_len(const vec2 *v)
{
    return sqrt(vec2_len_sqr(v));
}

void vec2_normalize(vec2 *dest, const vec2 *v)
{
    vec2_div(dest, v, vec2_len(v));
}

vec3 new_vec3(float x, float y, float z)
{
    vec3 v = {{x, y, z}};
    return v;
}

void vec3_add(vec3 *dest, const vec3 *u, const vec3 *v)
{
    dest->e[0] = u->e[0] + v->e[0];
    dest->e[1] = u->e[1] + v->e[1];
    dest->e[2] = u->e[2] + v->e[2];
}

void vec3_sub(vec3 *dest, const vec3 *u, const vec3 *v)
{
    dest->e[0] = u->e[0] - v->e[0];
    dest->e[1] = u->e[1] - v->e[1];
    dest->e[2] = u->e[2] - v->e[2];
}

void vec3_mult(vec3 *dest, const vec3 *v, float s)
{
    dest->e[0] = v->e[0] * s;
    dest->e[1] = v->e[1] * s;
    dest->e[2] = v->e[2] * s;
}

void vec3_div(vec3 *dest, const vec3 *v, float s)
{
    dest->e[0] = v->e[0] / s;
    dest->e[1] = v->e[1] / s;
    dest->e[2] = v->e[2] / s;
}

float vec3_dot(const vec3 *u, const vec3 *v)
{
    return u->e[0] * v->e[0] +
           u->e[1] * v->e[1] +
           u->e[2] * v->e[2];
}

void vec3_cross(vec3 *dest, const vec3 *u, const vec3 *v)
{
    dest->e[0] = u->e[1] * v->e[2] - u->e[2] * v->e[1];
    dest->e[1] = u->e[2] * v->e[0] - u->e[0] * v->e[2];
    dest->e[2] = u->e[0] * v->e[1] - u->e[1] * v->e[0];
}

float vec3_len_sqr(const vec3 *v)
{
    return v->e[0] * v->e[0] +
           v->e[1] * v->e[1] +
           v->e[2] * v->e[2];
}

float vec3_len(const vec3 *v)
{
    return sqrt(vec3_len_sqr(v));
}

void vec3_normalize(vec3 *dest, const vec3 *v)
{
    vec3_div(dest, v, vec3_len(v));
}

transform new_transform()
{
    transform t = {
        {{1.0f, 0.0f, 0.0f},
         {0.0f, 1.0f, 0.0f},
         {0.0f, 0.0f, 1.0f}}
    };

    return t;
}

// [dest] = [B] X [A]
transform transform_combine(transform *b, transform *a)
{
    transform dest;

    dest.mat[0][0] = a->mat[0][0] * b->mat[0][0] + a->mat[0][1] * b->mat[1][0] + a->mat[0][2] * b->mat[2][0];
    dest.mat[0][1] = a->mat[0][0] * b->mat[0][1] + a->mat[0][1] * b->mat[1][1] + a->mat[0][2] * b->mat[2][1];
    dest.mat[0][2] = a->mat[0][0] * b->mat[0][2] + a->mat[0][1] * b->mat[1][2] + a->mat[0][2] * b->mat[2][2];

    dest.mat[1][0] = a->mat[1][0] * b->mat[0][0] + a->mat[1][1] * b->mat[1][0] + a->mat[1][2] * b->mat[2][0];
    dest.mat[1][1] = a->mat[1][0] * b->mat[0][1] + a->mat[1][1] * b->mat[1][1] + a->mat[1][2] * b->mat[2][1];
    dest.mat[1][2] = a->mat[1][0] * b->mat[0][2] + a->mat[1][1] * b->mat[1][2] + a->mat[1][2] * b->mat[2][2];

    dest.mat[2][0] = a->mat[2][0] * b->mat[0][0] + a->mat[2][1] * b->mat[1][0] + a->mat[2][2] * b->mat[2][0];
    dest.mat[2][1] = a->mat[2][0] * b->mat[0][1] + a->mat[2][1] * b->mat[1][1] + a->mat[2][2] * b->mat[2][1];
    dest.mat[2][2] = a->mat[2][0] * b->mat[0][2] + a->mat[2][1] * b->mat[1][2] + a->mat[2][2] * b->mat[2][2];

    return dest;
}

void transform_rotate(transform *t, float rad)
{
    transform rot = {
        {{cos(rad), -sin(rad), 0.0f},
         {sin(rad),  cos(rad), 0.0f},
         {0.0f,      0.0f,     1.0f}}
    };

    *t = transform_combine(t, &rot);
}

void transform_scale(transform *t, float scalar)
{
    transform scale = {
        {{scalar, 0.0f,   0.0f},
         {0.0f,   scalar, 0.0f},
         {0.0f,   0.0f,   1.0f}}
    };

    *t = transform_combine(t, &scale);
}

void transform_translate(transform *t, float dx, float dy)
{
    transform translate = {
        {{1.0f, 0.0f,   dx},
         {0.0f, 1.0f,   dy},
         {0.0f, 0.0f, 1.0f}}
    };

    *t = transform_combine(t, &translate);
}

// transforms a 2d coordinate using the transformation matrix
// left-hand multiplication
// x' = Ax
void transform_apply(transform *t, vec2 *dest, vec2 *src)
{
    vec3 in_h = new_vec3(src->e[X_COOR], src->e[Y_COOR], 1.0f);
    vec3 out_h = new_vec3(0.0f, 0.0f, 1.0f);

    out_h.e[X_COOR] = t->mat[0][0] * in_h.e[X_COOR] + t->mat[0][1] * in_h.e[Y_COOR] + t->mat[0][2] * in_h.e[Z_COOR];
    out_h.e[Y_COOR] = t->mat[1][0] * in_h.e[X_COOR] + t->mat[1][1] * in_h.e[Y_COOR] + t->mat[1][2] * in_h.e[Z_COOR];
    out_h.e[Z_COOR] = t->mat[2][0] * in_h.e[X_COOR] + t->mat[2][1] * in_h.e[Y_COOR] + t->mat[2][2] * in_h.e[Z_COOR];

    dest->e[X_COOR] = out_h.e[X_COOR];
    dest->e[Y_COOR] = out_h.e[Y_COOR];
}
