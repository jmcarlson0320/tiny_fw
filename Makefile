CC = gcc
CFLAGS = -g -Wall

libtinyfw.a: tiny-core.o tiny-graphics.o tiny-vec.o tiny-utils.o
	ar rcs $@ $^

tiny-core.o: tiny-fw.h
tiny-graphics.o: tiny-fw.h
tiny-vec.o: tiny-fw.h
tiny-utils.o: tiny-fw.h

install: libtinyfw.a tiny-fw.h
	cp libtinyfw.a ~/lib/; cp default_font.ppm ~/lib/; cp tiny-fw.h ~/include/

clean:
	rm *.o *.a

.PHONY: clean install
