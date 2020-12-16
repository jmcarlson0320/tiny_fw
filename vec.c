#include "vec.h"
#include <math.h>

vec2 new_vec2(float x, float y)
{
    vec2 v = {{x, y}};
    return v;
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
