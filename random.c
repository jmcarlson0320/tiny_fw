#include "app.h"
#include "ui.h"
#include "utils.h"
#include "graphics.h"
#include "vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define WIDTH 480
#define HEIGHT 270

// begin random walker code
typedef struct {
    vec2 pos;
} Rand_walker;

static const vec2 up = {{-1, 0}};
static const vec2 down = {{1, 0}};
static const vec2 left = {{0, -1}};
static const vec2 right = {{0, 1}};

void walker_step(Rand_walker *r)
{
    int dir = rand() % 4;
    switch (dir) {
        case 0: vec2_add(&r->pos, &r->pos, &up); break;
        case 1: vec2_add(&r->pos, &r->pos, &down); break;
        case 2: vec2_add(&r->pos, &r->pos, &left); break;
        case 3: vec2_add(&r->pos, &r->pos, &right); break;
    }
}
// end random walker code

void update_ui_state(App *app, Ui_context *ui)
{
    ui_clear(ui);
    ui->mouse_x = app->mouse.x;
    ui->mouse_y = app->mouse.y;
    ui->mouse_dx = app->mouse.dx;
    ui->mouse_dy = app->mouse.dy;
    ui->mouse_button[0] = app->mouse.button[0];
    ui->mouse_button[1] = app->mouse.button[1];
    ui->mouse_pressed[0] = app->mouse.pressed[0];
    ui->mouse_pressed[1] = app->mouse.pressed[1];
    ui->mouse_released[0] = app->mouse.released[0];
    ui->mouse_released[1] = app->mouse.released[1];
}

int main(int argc, char *argv[])
{
    App app = app_create(WIDTH, HEIGHT);
    Ui_context ui = ui_create();

    Bitmap canvas = bitmap_create(app.graphics.width, app.graphics.height, app.graphics.pixels_rgb);
    Bitmap layer_1 = bitmap_allocate(app.graphics.width, app.graphics.height);

    graphics_output_set(&canvas);
    draw_fill_rect(0, 0, WIDTH - 1, HEIGHT - 1, 0x000000);
    graphics_output_set(&layer_1);
    draw_fill_transparent(0, 0, WIDTH - 1, HEIGHT - 1);

    srand(time(NULL));

    Rand_walker walker = {{{WIDTH / 2, HEIGHT / 2}}};

    app_start(&app);
    while (app.running) {
        app_update(&app);
        update_ui_state(&app, &ui);

        graphics_output_set(&canvas);
        draw_fill_rect(0, 0, WIDTH - 1, HEIGHT - 1, 0x00ff00);

        // update random walker and draw to transparent layer
        walker_step(&walker);
        graphics_output_set(&layer_1);
        draw_point(walker.pos.e[X_COOR], walker.pos.e[Y_COOR], 0xffffff);

        // draw layer_1 to canvas
        graphics_output_set(&canvas);
        draw_bitmap(&layer_1, 0, 0, WIDTH - 1, HEIGHT - 1, 0, 0);

        // close button
        if (do_button(&ui, 4, WIDTH - 11, 0, 10, 10))
            app.running = 0;
        draw_text("x", WIDTH - 9, 0, 0x000000);

        // draw cursor
        draw_fill_triangle(app.mouse.x, app.mouse.y, app.mouse.x + 10, app.mouse.y + 10, app.mouse.x, app.mouse.y + 14, 0xffffff);
        draw_triangle(app.mouse.x, app.mouse.y, app.mouse.x + 10, app.mouse.y + 10, app.mouse.x, app.mouse.y + 14, 0x000000);

        app_draw_graphics_to_screen(&app);
    }
    app_quit(&app);

    return 0;
}
