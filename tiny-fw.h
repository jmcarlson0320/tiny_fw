// HOW TO USE:
// // in main:
//
// App app = app_create(w, h);
//
// app_start(&app);
//
// while (app.running) {
//     app_update(&app);
//
//     // get keyboard/mouse state by looking at mouse.button[]/keyboard.down/mouse.x/mouse.y/etc
//
//     // draw graphics by writing to graphics.pixels_rgb[x + y * app.graphics.width]
//     // or with draw functions
//
//     app_draw_graphics(&app);
// }
//
// app_quit(&app);

#ifndef APP_H
#define APP_H

#define ALPHA_CHANNEL 0xFF00FF

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

enum MOUSE_BUTTIONS {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT
};

enum KEYS {
    KEY_UNKNOWN,
    KEY_A = 4,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_RETURN,
    KEY_ESCAPE,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_SPACE,
    KEY_RIGHT = 79,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP
};

typedef struct {
    int *pixels;
    int width;
    int height;
} Bitmap;

typedef struct {
    Bitmap bitmap;
    int char_width;
    int char_height;
} Font;

typedef struct {
    float e[2];
} vec2;

typedef struct {
    float e[3];
} vec3;

typedef vec2 point2;
typedef vec3 point3;
typedef vec3 color_rgb;

typedef struct {
    float mat[3][3];
} transform;

typedef struct {
    int running;

    struct graphics {
        int *pixels_rgb;
        int width;
        int height;
        int scale;
    } graphics;

    struct keyboard_state {
        int down[128];
        int pressed[128];
        int released[128];
    } keyboard;

    struct mouse_state {
        int x;
        int y;
        int dx;
        int dy;
        int button[2];
        int pressed[2];
        int released[2];
        int show_mouse;
    } mouse;

    struct timing_state {
        int ticks;
        float dt_sec;
    } time;

} App;

// tiny-core.c
App app_create(int width, int height, int scale);
void app_quit(App *app);
void app_start(App *app);
void app_update(App *app);
void app_draw_graphics(App *app);

// tiny-graphics.c
Bitmap bitmap_create(int width, int height, int *pixels);
Bitmap bitmap_allocate(int width, int height);
int bitmap_create_from_ppm(Bitmap *b, char *filename);
void bitmap_deallocate(Bitmap *b);
void graphics_output_set(Bitmap *b);
Bitmap graphics_output_get(void);

void draw_point(int x, int y, int color);
void draw_line(int x0, int y0, int x1, int y1, int color);
void draw_rect(int x0, int y0, int x1, int y1, int color);
void draw_fill_rect(int x0, int y0, int x1, int y1, int color);
void draw_fill_transparent(int x0, int y0, int x1, int y1);
void draw_circle(int x, int y, int r, int color);
void draw_fill_circle(int x, int y, int r, int color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color);
void draw_fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color);
void draw_interpolated_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color0, int color1, int color2);
void draw_bitmap(Bitmap *b, int src_x0, int src_y0, int src_x1, int src_y1, int dest_x, int dest_y);
void draw_bitmap_color(Bitmap *b, int src_x0, int src_y0, int src_x1, int src_y1, int dest_x, int dest_y, int color);
void draw_text(char *txt, int x, int y, int color);
void draw_wireframe(vec2 *points, int num_points, transform *t);

// tiny-utils.c
float lerp(float norm, float min, float max);
float norm(float value, float min, float max);
float map(float value, float srcMin, float srcMax, float destMin, float destMax);
int interpolate_color(float ratio, int color1, int color2);
int point_in_rect(int x, int y, int x0, int y0, int w, int h);

// tiny-vec.c
vec2 new_vec2(float x, float y);
vec2 vec2_unit_vec(float angle);
void vec2_add(vec2 *dest, const vec2 *u, const vec2 *v);
void vec2_sub(vec2 *dest, const vec2 *u, const vec2 *v);
void vec2_mult(vec2 *dest, const vec2 *v, float s);
void vec2_div(vec2 *dest, const vec2 *v, float s);
float vec2_dot(const vec2 *u, const vec2 *v);
float vec2_len_sqr(const vec2 *v);
float vec2_len(const vec2 *v);
void vec2_normalize(vec2 *dest, const vec2 *v);

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

transform new_transform();
transform transform_combine(transform *b, transform *a);
void transform_rotate(transform *t, float rad);
void transform_scale(transform *t, float scalar);
void transform_translate(transform *t, float dx, float dy);
void transform_apply(transform *t, vec2 *dest, vec2 *src);

#endif
