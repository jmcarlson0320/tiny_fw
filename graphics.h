// A simple graphics library that draws to a bitmap.
// To use, create a bitmap, then set it as the output for the
// library by calling graphics_output_set(&bitmap);
//
// To draw to an app's frame buffer, create a bitmap using
// the app's framebuffer, then set that bitmap as the graphics
// output.
//
// The file "default_font.ppm" must be in the working directory in
// order to draw text.
#ifndef GRAPHICS_H
#define GRAPHICS_H

#define ALPHA_CHANNEL 0xFF00FF

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

#endif
