#include <math.h>
#include <tiny-fw.h>
#include "gradient.h"

#define BACKGROUND_COLOR 0x000000
#define EXIT_KEY KEY_Q

App app;
int app_is_running = 0;

void init()
{
    app = app_create(WIDTH, HEIGHT, SCALE);
    app_start(&app);
    app_is_running = 1;
}

void update()
{
    app_update(&app);
    if (app.keyboard.pressed[EXIT_KEY]) {
        app_is_running = 0;
    }
    gradient_update(&app.keyboard);
}

void render()
{
    draw_fill_rect(0, 0, WIDTH, HEIGHT, BACKGROUND_COLOR);
    gradient_render();
    app_draw_graphics(&app);
}

void cleanup()
{
    app_quit(&app);
}

int main()
{
    init();
    while (app_is_running) {
        update();
        render();
    }
    cleanup();

    return 0;
}
