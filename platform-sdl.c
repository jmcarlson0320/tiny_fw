#include <SDL2/SDL.h>

#include "platform.h"

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *back_buffer;

void platform_init()
{
    SDL_Init(SDL_INIT_VIDEO);
}


void platform_create_window(int width, int height, int scale)
{
    SDL_CreateWindowAndRenderer(width * scale, height * scale, 0, &window, &renderer);
    SDL_RenderSetLogicalSize(renderer, width, height);
    back_buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, width, height);
}


int platform_get_time()
{
    return SDL_GetTicks();
}


void platform_delay(int ticks)
{
    SDL_Delay(ticks);
}


void platform_user_input(App *app)
{
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

    if (!app->mouse.show_mouse)
        SDL_ShowCursor(0);
}


void platform_draw_graphics(struct graphics graphics)
{
    SDL_UpdateTexture(back_buffer, NULL, graphics.pixels_rgb, graphics.width * sizeof(int));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, back_buffer, NULL, NULL);
    SDL_RenderPresent(renderer);
}


void platform_shutdown()
{
    SDL_Quit();
}
