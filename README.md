# graphics_lib
This is a tiny app/game framework that I'm using to practice programming/software engineering/writing libraries/etc. It is basically a toy for me to play around with.

It is an api with what I think are the bare-bones essentials for creating game-like apps: create a window, read keyboard/mouse, draw pixels to the window.

The framework's interface is completely abstract, with no details about opengl, xwindows, or any other library. At this point, it is implemented with SDL2,
but in the future I might try my own implementations for windows, linux, and mac, which could be a good exercise in separating platform dependent code from
platform independent code, as well as learning how those platforms work at a lower level.

tiny-fw.h shows the basics of how to use the core methods, the rest is hopefully self-explanitory.
