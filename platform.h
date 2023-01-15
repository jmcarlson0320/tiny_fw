#ifndef PLATFORM_H
#define PLATFORM_H

#include "tiny-fw.h"

void platform_init();
void platform_create_window(int width, int height, int scale);
int platform_get_time();
void platform_delay(int ticks);
void platform_user_input(App *app);
void platform_draw_graphics(struct graphics graphics);
void platform_shutdown();

#endif // PLATFORM_H
