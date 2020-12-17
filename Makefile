CC = gcc
CFLAGS = -g -Wall
LIBS = -lSDL2 -lm
EXE = app

$(EXE): emitter_test.o app.o graphics.o vec.o particle.o utils.o
	$(CC) -o $@ $^ $(LIBS)

emitter_test.o: app.h
app.o: app.h
graphics.o: app.h
vec.o: app.h
utils.o: app.h
particle.o: particle.h app.h

clean:
	rm *.o $(EXE)

.PHONY: clean
