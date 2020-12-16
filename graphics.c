#include "graphics.h"
#include "vec.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static Bitmap output;

static Font default_font;
static char *font_file_name = "default_font.ppm";
static int font_set = 0;

static void barycentric(point2 p, point2 a, point2 b, point2 c, float *u, float *v, float *w)
{
    vec2 v0;
    vec2 v1;
    vec2 v2;

    vec2_sub(&v0, &b, &a);
    vec2_sub(&v1, &c, &a);
    vec2_sub(&v2, &p, &a);

    float d00 = vec2_dot(&v0, &v0);
    float d01 = vec2_dot(&v0, &v1);
    float d11 = vec2_dot(&v1, &v1);
    float d20 = vec2_dot(&v2, &v0);
    float d21 = vec2_dot(&v2, &v1);
    float denom = d00 * d11 - d01 * d01;

    *v = (d11 * d20 - d01 * d21) / denom;
    *w = (d00 * d21 - d01 * d20) / denom;
    *u = 1.0f - *v - *w;
}

int interpolate_color(float ratio, int color1, int color2)
{
    int r1 = (color1 & 0x00ff0000) >> 16;
    int g1 = (color1 & 0x0000ff00) >> 8;
    int b1 = (color1 & 0x000000ff);

    int r2 = (color2 & 0x00ff0000) >> 16;
    int g2 = (color2 & 0x0000ff00) >> 8;
    int b2 = (color2 & 0x000000ff);

    if (ratio < 0.0f)
        ratio = 0.0f;
    else if (ratio > 1.0f)
        ratio = 1.0f;

    int r = ((1.0f - ratio) * (float) r1 + ratio * (float) r2);
    if (r > 255)
        r = 255;
    int g = ((1.0f - ratio) * (float) g1 + ratio * (float) g2);
    if (g > 255)
        g = 255;
    int b = ((1.0f - ratio) * (float) b1 + ratio * (float) b2);
    if (b > 255)
        b = 255;

    return r << 16 | g << 8 | b;
}

Bitmap bitmap_create(int width, int height, int *pixels)
{
    Bitmap b;
    b.width = width;
    b.height = height;
    b.pixels = pixels;
    return b;
}

Bitmap bitmap_allocate(int width, int height)
{
    Bitmap b;
    b = bitmap_create(width, height, malloc(width * height * sizeof(int)));
    return b;
}

void bitmap_deallocate(Bitmap *b)
{
    free(b->pixels);
    b->pixels = NULL;
    b->width = 0;
    b->height = 0;
}

int bitmap_create_from_ppm(Bitmap *b, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("unable to open %s\n", filename);
        return -1;
    }

    // read header
    int width;
    int height;
    if (fscanf(fp, "P3\n%d\n%d\n255\n", &width, &height) != 2) {
        printf("unable read %s\n", filename);
        return -1;
    }

    *b = bitmap_allocate(width, height);

    // scan file and fill in bitmap
    for (int i = 0; i < width * height; i++) {
        int red;
        int green;
        int blue;
        int color;
        fscanf(fp, "%d\n%d\n%d\n", &red, &green, &blue);
        color = red << 16 | green << 8 | blue;
        b->pixels[i] = color;
    }
    fclose(fp);

    return 0;
}

void graphics_output_set(Bitmap *b)
{
    output = *b;
}

Bitmap graphics_output_get(void)
{
    return output;
}

static Font font_create(int char_width, int char_height, Bitmap *b)
{
    Font f;
    f.char_width = char_width;
    f.char_height = char_height;
    f.bitmap = *b;
    return f;
}

static void graphics_font_set(Font *font)
{
    default_font = *font;
}

void draw_point(int x, int y, int color)
{
    if (x < 0 || y < 0 || x >= output.width || y >= output.height || color == ALPHA_CHANNEL)
        return;
    output.pixels[x + y * output.width] = color;
}

static void draw_horizontal_line(int y, int x0, int x1, int color)
{
    if (x0 > x1) {
        int tmp = x0;
        x0 = x1;
        x1 = tmp;
    }

    for (int x = x0; x <= x1; x++) {
        draw_point(x, y, color);
    }
}

static void draw_vertical_line(int x, int y0, int y1, int color)
{
    if (y0 > y1) {
        int tmp = y0;
        y0 = y1;
        y1 = tmp;
    }

    for (int y = y0; y <= y1; y++) {
        draw_point(x, y, color);
    }
}

void draw_line(int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    int num_steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float x_step = (float) dx / (float) num_steps;
    float y_step = (float) dy / (float) num_steps;

    float x = x0;
    float y = y0;
    for (int i = 0; i <= num_steps; i++) {
        draw_point(round(x), round(y), color);
        x += x_step;
        y += y_step;
    }
}

void draw_rect(int x0, int y0, int x1, int y1, int color)
{
    draw_horizontal_line(y0, x0, x1, color);
    draw_horizontal_line(y1, x0, x1, color);
    draw_vertical_line(x0, y0, y1, color);
    draw_vertical_line(x1, y0, y1, color);
}

void draw_fill_rect(int x0, int y0, int x1, int y1, int color)
{
    if (x0 > x1) {
        int tmp = x0;
        x0 = x1;
        x1 = tmp;
    }

    if (y0 > y1) {
        int tmp = y0;
        y0 = y1;
        y1 = tmp;
    }

    for (int y = y0; y <= y1; y++) {
        for (int x = x0; x <= x1; x++) {
            draw_point(x, y, color);
        }
    }
}

void draw_fill_transparent(int x0, int y0, int x1, int y1)
{
    if (x0 > x1) {
        int tmp = x0;
        x0 = x1;
        x1 = tmp;
    }

    if (y0 > y1) {
        int tmp = y0;
        y0 = y1;
        y1 = tmp;
    }

    for (int y = y0; y <= y1; y++) {
        for (int x = x0; x <= x1; x++) {
            int index = y * output.width + x;
            output.pixels[index] = ALPHA_CHANNEL;
        }
    }
}

void draw_circle(int x, int y, int r, int color)
{
    for (int j = -r; j <= r; j++) {
        for (int i = -r; i <= r; i++) {
            if (i * i + j * j < r * r + r && i * i + j * j > r * r - r) {
                draw_point(x + i, y + j, color);
            }
        }
    }
}

void draw_fill_circle(int x, int y, int r, int color)
{
    for (int j = -r; j <= r; j++) {
        for (int i = -r; i <= r; i++) {
            if (i * i + j * j < r * r + r) {
                draw_point(x + i, y + j, color);
            }
        }
    }
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color)
{
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}

void draw_fill_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color)
{
    int min_x = fmin(x0, x1);
    min_x = fmin(min_x, x2);

    int max_x = fmax(x0, x1);
    max_x = fmax(max_x, x2);

    int min_y = fmin(y0, y1);
    min_y = fmin(min_y, y2);

    int max_y = fmax(y0, y1);
    max_y = fmax(max_y, y2);

    for (int y = min_y; y < max_y; y++) {
        for (int x = min_x; x < max_x; x++) {
            float u;
            float v;
            float w;
            barycentric(new_vec2(x, y), new_vec2(x0, y0), new_vec2(x1, y1), new_vec2(x2, y2), &u, &v, &w);
            if (0 < u && u < 1 && 0 < v && v < 1 && 0 < w && w < 1) {
                draw_point(x, y, color);
            }
        }
    }
}

void draw_interpolated_triangle(int x0, int y0, int x1, int y1, int x2, int y2, int color0, int color1, int color2)
{
    int min_x = fmin(x0, x1);
    min_x = fmin(min_x, x2);

    int max_x = fmax(x0, x1);
    max_x = fmax(max_x, x2);

    int min_y = fmin(y0, y1);
    min_y = fmin(min_y, y2);

    int max_y = fmax(y0, y1);
    max_y = fmax(max_y, y2);

    for (int y = min_y; y < max_y; y++) {
        for (int x = min_x; x < max_x; x++) {
            float u;
            float v;
            float w;
            barycentric(new_vec2(x, y), new_vec2(x0, y0), new_vec2(x1, y1), new_vec2(x2, y2), &u, &v, &w);
            if (0 < u && u < 1 && 0 < v && v < 1 && 0 < w && w < 1) {
                // interpolate the colors and add them 
                int blended_color = interpolate_color(v, color0, color1);
                blended_color = interpolate_color(w, blended_color, color2);
                draw_point(x, y, blended_color);
            }
        }
    }
}

void draw_bitmap(Bitmap *b, int src_x0, int src_y0, int src_x1, int src_y1, int dest_x, int dest_y)
{
    if (src_x0 < 0 || src_y0 < 0 || src_x1 < 0 || src_y1 < 0) {
        return;
    }
    if (src_x0 >= b->width || src_y0 >= b->height || src_x1 >= b->width || src_y1 >= b->height) {
        return;
    }

    if (src_x0 > src_x1) {
        int tmp = src_x0;
        src_x0 = src_x1;
        src_x1 = tmp;
    }

    if (src_y0 > src_y1) {
        int tmp = src_y0;
        src_y0 = src_y1;
        src_y1 = tmp;
    }

    for (int y = 0; y < src_y1 - src_y0; y++) {
        for (int x = 0; x < src_x1 - src_x0; x++) {
            draw_point(dest_x + x, dest_y + y, b->pixels[src_x0 + x + (src_y0 + y) * b->width]);
        }
    }
}

void draw_bitmap_color(Bitmap *b, int src_x0, int src_y0, int src_x1, int src_y1, int dest_x, int dest_y, int color)
{
    if (src_x0 < 0 || src_y0 < 0 || src_x1 < 0 || src_y1 < 0) {
        return;
    }
    if (src_x0 >= b->width || src_y0 >= b->height || src_x1 >= b->width || src_y1 >= b->height) {
        return;
    }

    if (src_x0 > src_x1) {
        int tmp = src_x0;
        src_x0 = src_x1;
        src_x1 = tmp;
    }

    if (src_y0 > src_y1) {
        int tmp = src_y0;
        src_y0 = src_y1;
        src_y1 = tmp;
    }

    for (int y = 0; y < src_y1 - src_y0; y++) {
        for (int x = 0; x < src_x1 - src_x0; x++) {
            int bitmap_color = b->pixels[src_x0 + x + (src_y0 + y) * b->width];
            if (bitmap_color != ALPHA_CHANNEL)
                draw_point(dest_x + x, dest_y + y, color);
        }
    }
}

static void use_default_font(void)
{
    Bitmap font_bitmap;
    bitmap_create_from_ppm(&font_bitmap, font_file_name);
    Font font = font_create(7, 9, &font_bitmap);
    graphics_font_set(&font);
}

void draw_text(char *txt, int x, int y, int color)
{
    // the first time draw_text is called, if no font was set, use the default
    if (!font_set) {
        use_default_font();
        font_set = 1;
    }

    int char_count = 0;
    int row_count = 0;

    int table_width = default_font.bitmap.width / default_font.char_width;

    while (*txt) {
        if ((*txt < ' ' || '~' < *txt) && *txt != '\n')
            return;

        while (*txt == '\n') {
            char_count = 0;
            row_count++;
            if (!*++txt)
                return;
        }

        int font_code = (int) *txt - ' ';
        int font_table_row = font_code / table_width;
        int font_table_col = font_code % table_width;
        int x0 = font_table_col * default_font.char_width;
        int y0 = font_table_row * default_font.char_height;
        int x1 = font_table_col * default_font.char_width + default_font.char_width;
        int y1 = font_table_row * default_font.char_height + default_font.char_height;
        int cursor_col = x + char_count * default_font.char_width;
        int cursor_row = y + row_count * default_font.char_height;

        draw_bitmap_color(&default_font.bitmap, x0, y0, x1, y1, cursor_col, cursor_row, color);

        txt++;
        char_count++;
    }
}
