CC = gcc
CFLAGS = -g -Wall
BINARY = ~/lib/
INCLUDE = ~/include/

libtinyfw.a: tiny-core.o tiny-graphics.o tiny-vec.o tiny-utils.o
	ar rcs $@ $^

tiny-core.o: tiny-fw.h
tiny-graphics.o: tiny-fw.h
tiny-vec.o: tiny-fw.h
tiny-utils.o: tiny-fw.h

install: libtinyfw.a tiny-fw.h
	cp libtinyfw.a $(BINARY); cp default_font.ppm $(BINARY); cp tiny-fw.h $(INCLUDE)

clean:
	rm *.o *.a

.PHONY: clean install
