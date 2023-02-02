#include <tiny-fw.h>

#define WIDTH 256
#define HEIGHT 256
#define SCALE 3
#define BACKGROUND_COLOR 0xffffff
#define EXIT_KEY KEY_Q
#define TEXT_COLOR 0x000000

char *MSG = "2D Graphics Program Skeleton\n"
            "press 'q' to quit";

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
}

void render()
{
    draw_fill_rect(0, 0, WIDTH, HEIGHT, BACKGROUND_COLOR);
    draw_text(MSG, 0, 0, TEXT_COLOR);
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
