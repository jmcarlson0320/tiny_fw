// An example program using the app framework, the graphics library, and the imui framework.
// Consists of three knobs that control the rgb components of the background, a button
// for closing the app, and some stats. 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tiny-fw.h"
#include "ui.h"

#define SCALE_FACTOR 3
#define WIDTH 320
#define HEIGHT 240

enum elem_id {
    RED_KNOB = 1,
    GREEN_KNOB,
    BLUE_KNOB,
    EXIT_BUTTON,
    NUM_UI_ELEMS
};

// the application is responsible for getting
// events to the ui context. In this case, we 
// directly update the state because our app api
// hides events from the user and instead exposes
// a global per-frame state. We could also
// generate/pass events via function calls, ie
// ui_mouse_event(type, x, y, ...).
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
    App app = app_create(WIDTH, HEIGHT, SCALE_FACTOR);
    Ui_context ui = ui_create();

    // make a bitmap from the app's pixel array
    Bitmap canvas = bitmap_create(app.graphics.width, app.graphics.height, app.graphics.pixels_rgb);

    // setup graphics to draw to the app's framebuffer
    graphics_output_set(&canvas);

    char txt_buffer[256];
    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;
    int bg_color = 0x000000;

    app_start(&app);

    while (app.running) {

        app_update(&app);

        update_ui_state(&app, &ui);

        // clear screen
        draw_fill_rect(0, 0, WIDTH - 1, HEIGHT - 1, bg_color);

        // immediate mode ui widgets
        // knobs to change background color components
        do_knob(&ui, RED_KNOB, WIDTH / 2 - 50, HEIGHT / 2, 20, &red, 0.0f, 1.0f);
        do_knob(&ui, GREEN_KNOB, WIDTH / 2, HEIGHT / 2, 20, &green, 0.0f, 1.0f);
        do_knob(&ui, BLUE_KNOB, WIDTH / 2 + 50, HEIGHT / 2, 20, &blue, 0.0f, 1.0f);

        // set background color using knob settings
        int r = (int) map(red, 0, 1, 0, 255);
        int g = (int) map(green, 0, 1, 0, 255);
        int b = (int) map(blue, 0, 1, 0, 255);
        bg_color = r << 16 | g << 8 | b;

        // generate stats string
        sprintf(txt_buffer, "Background Color:0x%x\n"
                            "MouseX:%d\n"
                            "MouseY:%d\n"
                            "r:%f\n"
                            "g:%f\n"
                            "b:%f\n", bg_color, app.mouse.x, app.mouse.y, red, green, blue);

        // draw the stats string
        draw_text(txt_buffer, 0, 0, 0xffffff);

        // make a close button
        if (do_button(&ui, EXIT_BUTTON, WIDTH - 11, 0, 10, 10))
            app.running = 0;
        draw_text("x", WIDTH - 9, 0, 0x000000);

        // draw a triangle shaped cursor
        draw_fill_triangle(app.mouse.x, app.mouse.y, app.mouse.x + 10, app.mouse.y + 10, app.mouse.x, app.mouse.y + 14, 0xffffff);
        draw_triangle(app.mouse.x, app.mouse.y, app.mouse.x + 10, app.mouse.y + 10, app.mouse.x, app.mouse.y + 14, 0x000000);

        app_draw_graphics(&app);
    }
    app_quit(&app);

    return 0;
}
