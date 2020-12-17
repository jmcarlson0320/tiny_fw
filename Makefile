CC = gcc
CFLAGS = -g -Wall
LIBS = -lSDL2 -lm
EXE = app

$(EXE): emitter_test.o tiny-core.o tiny-graphics.o tiny-vec.o particle.o tiny-utils.o
	$(CC) -o $@ $^ $(LIBS)

emitter_test.o: tiny-fw.h
app.o: tiny-fw.h
graphics.o: tiny-fw.h
vec.o: tiny-fw.h
utils.o: tiny-fw.h
particle.o: particle.h tiny-fw.h

clean:
	rm *.o $(EXE)

.PHONY: clean
