CC = gcc
CFLAGS = -g -Wall
LIBS = -lSDL2 -lm

libtinyfw.a: tiny-core.o tiny-graphics.o tiny-vec.o tiny-utils.o
	ar rcs $@ $^

tiny-core.o: tiny-fw.h
tiny-graphics.o: tiny-fw.h
tiny-vec.o: tiny-fw.h
tiny-utils.o: tiny-fw.h

clean:
	rm *.o *.a

.PHONY: clean
