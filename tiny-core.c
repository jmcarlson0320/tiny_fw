#include <stdlib.h>
#include "tiny-fw.h"
#include "platform.h"

App app_create(int width, int height, int scale)
{
    App app;
    app.graphics.pixels_rgb = malloc(width * height * sizeof(int));
    app.graphics.width = width;
    app.graphics.height = height;
    app.graphics.scale = scale;

    Bitmap canvas = bitmap_create(width, height, app.graphics.pixels_rgb);
    graphics_output_set(&canvas);

    app.mouse.x = 0;
    app.mouse.y = 0;
    app.mouse.button[0] = 0;
    app.mouse.button[1] = 0;
    app.mouse.show_mouse = 0;

    for (int i = 0; i < 128; i++) {
        app.keyboard.down[i] = 0;
        app.keyboard.pressed[i] = 0;
        app.keyboard.released[i] = 0;
    }

    app.time.ticks = platform_get_time();
    app.time.dt_sec = 17.0f / 1000.0f;

    app.running = 0;

    return app;
}


void app_start(App *app)
{
    int w = app->graphics.width;
    int h = app->graphics.height;
    int scale = app->graphics.scale;

    platform_init();
    platform_create_window(w, h, scale);

    app->running = 1;
}


void app_update(App *app)
{
    int cur_time = platform_get_time();
    app->time.dt_sec = (cur_time - app->time.ticks) / 1000.0f;
    app->time.ticks = cur_time;
    int delay = 17 - app->time.dt_sec * 1000.0f;
    if (delay < 0)
        delay = 0;
    platform_delay(delay);

    // clear the "mouse just pressed/released" state
    app->mouse.pressed[MOUSE_BUTTON_LEFT] = 0;
    app->mouse.pressed[MOUSE_BUTTON_RIGHT] = 0;
    app->mouse.released[MOUSE_BUTTON_LEFT] = 0;
    app->mouse.released[MOUSE_BUTTON_RIGHT] = 0;
    app->mouse.dx = 0;
    app->mouse.dy = 0;

    // clear the "keyboard just pressed/released" state
    for (int i = 0; i < 128; i++) {
        app->keyboard.pressed[i] = 0;
        app->keyboard.released[i] = 0;
    }

    platform_user_input(app);
}


void app_draw_graphics(App *app)
{
    platform_draw_graphics(app->graphics);
}


void app_quit(App *app)
{
    platform_shutdown();
    free(app->graphics.pixels_rgb);
    app->graphics.pixels_rgb = NULL;
}
