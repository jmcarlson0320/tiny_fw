// Simple app interface implemented with SDL
#include "tiny-fw.h"

#include <SDL2/SDL.h>

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *back_buffer;

App app_create(int width, int height)
{
    App app;
    app.graphics.pixels_rgb = malloc(width * height * sizeof(int));
    app.graphics.width = width;
    app.graphics.height = height;

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

    app.time.ticks = 0;
    app.time.dt_sec = 17.0f / 1000.0f;

    app.running = 0;

    return app;
}

void app_start(App *app)
{
    // setup SDL for hw rendering
    int w = app->graphics.width;
    int h = app->graphics.height;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
    SDL_RenderSetLogicalSize(renderer, w, h);
    back_buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, w, h);

    app->running = 1;
}

void app_update(App *app)
{
    // perform timing calculations
    // delay for a fixed frame-rate
    int elapsed = SDL_GetTicks() - app->time.ticks;
    int delay = 17 - elapsed;
    if (delay < 0)
        delay = 0;
    SDL_Delay(delay);
    app->time.ticks = SDL_GetTicks();

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

    // process SDL events and update app state accordingly
    // these are the "output" variables to be read by the user
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            app->running = 0;
        } else if (event.type == SDL_KEYDOWN) {
            SDL_KeyboardEvent *keyboard = (SDL_KeyboardEvent *) &event;
            if (!keyboard->repeat) {
                int key = keyboard->keysym.scancode;
                if (key < 128) {
                    app->keyboard.down[key] = 1;
                    app->keyboard.pressed[key] = 1;
                }
            }
        } else if (event.type == SDL_KEYUP) {
            SDL_KeyboardEvent *keyboard = (SDL_KeyboardEvent *) &event;
            if (!keyboard->repeat) {
                int key = keyboard->keysym.scancode;
                if (key < 128) {
                    app->keyboard.down[key] = 0;
                    app->keyboard.released[key] = 1;
                }
            }
        } else if (event.type == SDL_MOUSEMOTION) {
            SDL_MouseMotionEvent *mouse = (SDL_MouseMotionEvent *) &event;
            app->mouse.dx = mouse->x - app->mouse.x;
            app->mouse.dy = mouse->y - app->mouse.y;
            app->mouse.x = mouse->x;
            app->mouse.y = mouse->y;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            SDL_MouseButtonEvent *mouse = (SDL_MouseButtonEvent *) &event;
            if (mouse->button == SDL_BUTTON_LEFT) {
                app->mouse.button[MOUSE_BUTTON_LEFT] = 1;
                app->mouse.pressed[MOUSE_BUTTON_LEFT] = 1;
            } else if (mouse->button == SDL_BUTTON_RIGHT) {
                app->mouse.button[MOUSE_BUTTON_RIGHT] = 1;
                app->mouse.pressed[MOUSE_BUTTON_RIGHT] = 1;
            }
        } else if (event.type == SDL_MOUSEBUTTONUP) {
            SDL_MouseButtonEvent *mouse = (SDL_MouseButtonEvent *) &event;
            if (mouse->button == SDL_BUTTON_LEFT) {
                app->mouse.button[0] = 0;
                app->mouse.released[MOUSE_BUTTON_LEFT] = 1;
            } else if (mouse->button == SDL_BUTTON_RIGHT) {
                app->mouse.button[1] = 0;
                app->mouse.released[MOUSE_BUTTON_RIGHT] = 1;
            }
        }
    }

    // we also scan the "input" variables meant to be set by the user
    if (!app->mouse.show_mouse)
        SDL_ShowCursor(0);
}

void app_draw_graphics(App *app)
{
    // load app's pixel buffer data into a texture
    SDL_UpdateTexture(back_buffer, NULL, app->graphics.pixels_rgb, app->graphics.width * sizeof(int));

    // clear SDL's renderer
    SDL_RenderClear(renderer);

    // give the texture to SDL's renderer
    SDL_RenderCopy(renderer, back_buffer, NULL, NULL);

    // draw the texture
    SDL_RenderPresent(renderer);
}

void app_quit(App *app)
{
    SDL_Quit();
    free(app->graphics.pixels_rgb);
    app->graphics.pixels_rgb = NULL;
}
