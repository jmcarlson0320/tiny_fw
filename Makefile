CC = gcc
CFLAGS = -g -Wall
LIBS = -lSDL2 -lm
EXE = app

$(EXE): emitter_test.o app.o graphics.o vec.o particle.o utils.o
	$(CC) -o $@ $^ $(LIBS)

emitter_test.o: app.h graphics.h particle.h
app.o: app.h
graphics.o: graphics.h vec.h
vec.o: vec.h
particle.o: particle.h graphics.h vec.h
utils.o: utils.h

clean:
	rm *.o $(EXE)

.PHONY: clean
