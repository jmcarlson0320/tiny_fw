#ifndef VEC_H
#define VEC_H

enum axis {
        X_COOR,
        Y_COOR,
        Z_COOR
};

enum color_comp {
        RED_COMP,
        GREEN_COMP,
        BLUE_COMP
};

typedef struct {
        float e[2];
} vec2;

typedef struct {
        float e[3];
} vec3;

typedef vec2 point2;
typedef vec3 point3;
typedef vec3 color_rgb;

// 2d vector
vec2 new_vec2(float x, float y);
void vec2_add(vec2 *dest, const vec2 *u, const vec2 *v);
void vec2_sub(vec2 *dest, const vec2 *u, const vec2 *v);
void vec2_mult(vec2 *dest, const vec2 *v, float s);
void vec2_div(vec2 *dest, const vec2 *v, float s);
float vec2_dot(const vec2 *u, const vec2 *v);
float vec2_len_sqr(const vec2 *v);
float vec2_len(const vec2 *v);
void vec2_normalize(vec2 *dest, const vec2 *v);

// 3d vector
vec3 new_vec3(float x, float y, float z);
void vec3_add(vec3 *dest, const vec3 *u, const vec3 *v);
void vec3_sub(vec3 *dest, const vec3 *u, const vec3 *v);
void vec3_mult(vec3 *dest, const vec3 *v, float s);
void vec3_div(vec3 *dest, const vec3 *v, float s);
float vec3_dot(const vec3 *u, const vec3 *v);
void vec3_cross(vec3 *dest, const vec3 *u, const vec3 *v);
float vec3_len_sqr(const vec3 *v);
float vec3_len(const vec3 *v);
void vec3_normalize(vec3 *dest, const vec3 *v);

#endif
