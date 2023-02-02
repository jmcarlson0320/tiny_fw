#ifndef UI_H
#define UI_H

enum {
    MOUSE_LEFT,
    MOUSE_RIGHT
};

typedef struct {
    int active;
    int hot;
    int dragged;
    int mouse_x;
    int mouse_y;
    int mouse_dx;
    int mouse_dy;
    int mouse_button[2];
    int mouse_pressed[2];
    int mouse_released[2];
} Ui_context;

Ui_context ui_create(void);

void ui_clear(Ui_context *ui);

int do_button(Ui_context *ui, int id, int x, int y, int w, int h);
int do_knob(Ui_context *ui, int id, int x, int y, int rad, float *param, float min, float max);
int do_slider(Ui_context *ui, int id, int x, int y, float *param);

#endif
