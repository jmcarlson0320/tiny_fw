// A simple application interface for making games and other
// interactive, graphical apps.
//
// HOW TO USE:
//
// App app = app_create(w, h);
// app_start(&app);
// while (app.running) {
//     app_update(&app);
//
//     // get mouse/keyboard state by looking at button[]/pressed[]/x/y
//     // draw graphics by writing to pixels_rgb array
//
//     app_draw_graphics_to_screen(&app);
// }
// app_quit(&app);

#ifndef APP_H
#define APP_H

enum MOUSE_BUTTIONS {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT
};

enum KEYS {
    KEY_UNKNOWN,
    KEY_A = 4,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_RETURN,
    KEY_ESCAPE,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_SPACE,
    KEY_RIGHT = 79,
    KEY_LEFT,
    KEY_DOWN,
    KEY_UP
};

typedef struct {
    int running;

    struct graphics {
        int *pixels_rgb;
        int width;
        int height;
    } graphics;

    struct keyboard_state {
        int down[128];
        int pressed[128];
        int released[128];
    } keyboard;

    struct mouse_state {
        int x;
        int y;
        int dx;
        int dy;
        int button[2];
        int pressed[2];
        int released[2];
        int show_mouse;
    } mouse;

    struct timing_state {
        int ticks;
        float dt_sec;
    } time;

} App;

/*
 * initializes the app structure, allocates memory for the state
 * arrays and the graphics pixel buffer
 * */
App app_create(int width, int height);

/*
 * frees the app state and closes the window
 * */
void app_quit(App *app);

/*
 * creates a window for the app and puts it on the screen.
 * the window remains until app_quit() is called.
 * */
void app_start(App *app);

/*
 * fills in the app structure with all of the real-time state:
 * all the sub-structures that have "state" in their name.
 * This should be called at the top of every frame.
 * */
void app_update(App *app);

/*
 * presents the graphics buffer to the window.
 * This should be called at the end of every frame.
 * */
void app_draw_graphics_to_screen(App *app);

#endif
