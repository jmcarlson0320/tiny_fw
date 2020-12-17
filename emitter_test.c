#include "app.h"
#include "graphics.h"
#include "particle.h"

#define SCALE_FACTOR 3
#define WIDTH (1920 / SCALE_FACTOR)
#define HEIGHT (1080 / SCALE_FACTOR)

int main(int argc, char *argv[])
{
    App app = app_create(WIDTH, HEIGHT);
    Bitmap canvas = bitmap_create(app.graphics.width, app.graphics.height, app.graphics.pixels_rgb);
    Emitter e = emitter_create(100, 100, 100);

    graphics_output_set(&canvas);
    app_start(&app);
    while (app.running) {
        app_update(&app);
        if (app.mouse.button[MOUSE_BUTTON_LEFT])
            app.running = 0;
        if (app.keyboard.down[KEY_E]) {
            e.pos.e[X_COOR] = app.mouse.x;
            e.pos.e[Y_COOR] = app.mouse.y;
            emitter_update(&e, app.time.dt_sec);
            draw_fill_rect(0, 0, WIDTH - 1, HEIGHT - 1, 0x000000);
            emitter_render(&e);
        }
        draw_text("1234abcd!@#$", 0, 0, 0x00ffff);
        app_draw_graphics_to_screen(&app);
    }
    app_quit(&app);
    emitter_destroy(&e);

    return 0;
}
