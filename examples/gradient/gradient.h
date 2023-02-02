#ifndef GRADIENT_H
#define GRADIENT_H

#include <tiny-fw.h>

#define WIDTH 256
#define HEIGHT 256
#define SCALE 3
#define TEXT_COLOR 0xffffff

void gradient_update(struct keyboard_state *keys);
void gradient_render(void);

#endif // GRADIENT_H
