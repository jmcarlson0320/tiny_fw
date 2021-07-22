# Tiny Framework

### Features

- Create a window
- Read mouse/keyboard input
- Manually set pixels in a framebuffer
- Includes 2D graphics library
- Includes 2D/3D vector library
- Includes Utility functions

### Background

This is a small app/game framework that I'm using to practice programming/software engineering/writing libraries/etc.

The API exposes the bare-bones essentials for creating game-like apps: create a window, read keyboard/mouse, draw pixels to the window.

The framework's interface is completely abstract, with no details about opengl, xwindows, or any other library. At this point, it is implemented with SDL2,
but in the future I might try my own implementations for windows, linux, and mac, which could be a good exercise in separating platform dependent code from
platform independent code, as well as learning how those platforms work at a lower level.

tiny-fw.h shows the basics of how to use the core methods inside of a "game loop", the rest is hopefully self-explanitory.

The graphics routines are heavily inspired by an example in an article titled "Immediate Mode GUIs" by Sean T. Barrett, from Game Developer Magazine, Sept. 2005.

The idea of a "super-struct" that gives access to all the relevant app state was taken from a youtuber named "Bitwise": [https://www.youtube.com/watch?v=NG_mUhc8LRw].

## Installation

Tiny Framework requires SDL2.0. Make sure it is installed and set up on your system before continuing.

Download the library.
```bash
git clone https://github.com/jmcarlson0320/tiny-fw.git
```

(Optional) Set the binary and header installation directories in the Makefile. Default is ~/lib and ~/include.
```bash
BINARY = path_to_your_libraries_folder
INCLUDE = path_to_your_headers_folder
```

Compile and install.
```bash
make install
```

## Usage

Include the library in your source code.
```C
#include <tiny-fw.h>
```

Compilation (using default installation paths).
```bash
gcc -o executable main.c -I/home/user/include -L/home/user/lib -ltinyfw -lm -lSDL2
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)
