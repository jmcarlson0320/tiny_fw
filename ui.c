#include "ui.h"
#include "graphics.h"
#include "utils.h"
#include <math.h>

typedef struct {
    int state;
    int event;
    int next_state;
    void (*function)(void);
} Transition;

enum states {
    NUM_STATES
};

enum events {
    NUM_EVENTS
};

Ui_context ui_create(void)
{
    Ui_context u;

    u.active = 0;
    u.hot = 0;
    u.dragged = 0;

    u.mouse_x = 0;
    u.mouse_y = 0;
    u.mouse_dx = 0;
    u.mouse_dy = 0;
    u.mouse_button[0] = 0;
    u.mouse_button[1] = 0;
    u.mouse_pressed[0] = 0;
    u.mouse_pressed[1] = 0;
    u.mouse_released[0] = 0;
    u.mouse_released[1] = 0;

    return u;
}

void ui_clear(Ui_context *ui)
{
    ui->mouse_pressed[0] = 0;
    ui->mouse_pressed[1] = 0;
    ui->mouse_released[0] = 0;
    ui->mouse_released[1] = 0;
    ui->mouse_dx = 0;
    ui->mouse_dy = 0;
}

static int do_button_logic(Ui_context *ui, int id, int x, int y, int w, int h)
{
    int result = 0;
    int m_x = ui->mouse_x;
    int m_y = ui->mouse_y;

    // states
    int active = (ui->active == id);
    int hot = (ui->hot == id);
    int idle = (!hot && !active);

    // signals
    int pressed = ui->mouse_pressed[MOUSE_LEFT];
    int released = ui->mouse_released[MOUSE_LEFT];
    int over = point_in_rect(m_x, m_y, x, y, w, h);

    // finite state automaton
    if (active) {
        if (released) {
            ui->active = 0;
            ui->hot = id;
            result = 1;
        } else if (!over) {
            ui->active = 0;
        }
    } else if (hot) {
        if (pressed) {
            ui->active = id;
        } else if (!over) {
            ui->hot = 0;
        }
    } else if (idle) {
        if (over) {
            ui->hot = id;
        }
    }

    return result;
}

static int do_draggable_logic(Ui_context *ui, int id, int *dx, int *dy)
{
    int result = 0;

    // states
    int dragged = (ui->dragged == id);
    int active = (ui->active == id);

    // signals
    int down = ui->mouse_button[MOUSE_LEFT] == !ui->mouse_pressed[MOUSE_LEFT];
    int released = ui->mouse_released[MOUSE_LEFT];

    // new transition to dragged state
    // new state: dragged
    if (active) {
        if (down) {
            ui->dragged = id;
            ui->active = 0;
        }
    } else if (dragged) {
        *dx = ui->mouse_dx;
        *dy = ui->mouse_dy;
        if (*dx || *dy)
            result = 1;
        if (released) {
            ui->dragged = 0;
        }
    }

    return result;
}

int do_button(Ui_context *ui, int id, int x, int y, int w, int h)
{
    int result = do_button_logic(ui, id, x, y, w, h);

    // render button
    int color;
    if (ui->active == id)
        color = 0xffffff;
    else if (ui->hot == id)
        color = 0xffff00;
    else
        color = 0xff0000;
    draw_fill_rect(x, y, x + w, y + h, color);
    draw_rect(x, y, x + w, y + h, 0x000000);

    return result;
}

int do_knob(Ui_context *ui, int id, int x, int y, int rad, float *param, float min, float max)
{
    do_button_logic(ui, id, x - rad, y - rad, 2 * rad, 2 * rad);

    int drag_x = 0;
    int drag_y = 0;
    int was_turned = do_draggable_logic(ui, id, &drag_x, &drag_y);
    int parameter_changed = 0;

    if (was_turned) {
        float change = map((float) drag_y, 0, 200, min, max);
        *param -= change;
        if (*param < min) {
            *param = min;
            parameter_changed = 0;
        } else if (*param > max) {
            *param = max;
            parameter_changed = 0;
        }
    }

    // render knob
    int color;
    if (ui->active == id || ui->dragged == id) color = 0xffffff;
    else if (ui->hot == id) color = 0xffff00;
    else color = 0xff0000;
    float angle = 3.0f * M_PI / 4.0f + map(*param, min, max, 0.0f, 6.0f * M_PI / 4.0f);
    float end_x = (float) rad * cos(angle) + x;
    float end_y = (float) rad * sin(angle) + y;
    draw_fill_circle(x, y, rad, color);
    draw_circle(x, y, rad, 0x000000);
    draw_line(x, y, end_x, end_y, 0x000000);

    return parameter_changed;
}

int do_slider(Ui_context *ui, int id, int x, int y, float *param)
{
    return 0;
}
