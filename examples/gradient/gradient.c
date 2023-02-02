#include "gradient.h"
#include <tiny-fw.h>
#include <math.h>

enum program {
    GRADIENT,
    SIN_FUNC,
    NONE
};

static int cur_program = NONE;
static char *MSG =
"2D Graphics Program Skeleton\n"
"------------------------------\n"
"press 's' for sin function\n"
"press 'g' for gradient\n"
"press 'b' for black background\n"
"press 'q' to quit";

static int combine_color(int r, int g, int b)
{
    return r << 16 | g << 8 | b;
}

void gradient_update(struct keyboard_state *keys)
{
    if (keys->pressed[KEY_G]) {
        cur_program = GRADIENT;
    }
    if (keys->pressed[KEY_S]) {
        cur_program = SIN_FUNC;
    }
    if (keys->pressed[KEY_B]) {
        cur_program = NONE;
    }
}

void gradient_render(void)
{
    if (cur_program == GRADIENT) {
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                int color = combine_color(x, y, 128);
                draw_point(x, y, color);
            }
        }
    } else if (cur_program == SIN_FUNC) {
        for (int x = 0; x < WIDTH; x++) {
            for (int y = 0; y < HEIGHT; y++) {
                int color = combine_color(0, (int)(128 + 128 * sin(x / 8.0f)), 0);
                draw_point(x, y, color);
            }
        }
    }
    draw_text(MSG, 0, 0, TEXT_COLOR);
}
