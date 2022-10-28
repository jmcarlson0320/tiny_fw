DEFAULT_FONT_ABS_PATH = "/Users/jmc/lib/default_font.ppm"
CC = gcc
CFLAGS = -g -Wall -DFONT='$(DEFAULT_FONT_ABS_PATH)' -I/opt/homebrew/Cellar/sdl2/2.0.22/include
BINARY_INSTALL_LOCATION = ~/lib/
INCLUDE_INSTALL_LOCATION = ~/include/

libtinyfw.a: tiny-core.o tiny-graphics.o tiny-vec.o tiny-utils.o
	ar rcs $@ $^ 

tiny-core.o: tiny-fw.h
tiny-graphics.o: tiny-fw.h
tiny-vec.o: tiny-fw.h
tiny-utils.o: tiny-fw.h

install: libtinyfw.a tiny-fw.h
	cp libtinyfw.a $(BINARY_INSTALL_LOCATION); cp default_font.ppm $(BINARY_INSTALL_LOCATION); cp tiny-fw.h $(INCLUDE_INSTALL_LOCATION)

clean:
	rm *.o *.a

.PHONY: clean install
