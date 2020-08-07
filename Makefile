CC = gcc
CFLAGS = -g -Wall
LIBS = -lSDL2 -lm
EXE = app

$(EXE): main.o app.o graphics.o vec.o ui.o utils.o
	$(CC) -o $@ $^ $(LIBS)

main.o: graphics.h vec.h
utils.o: utils.h
app.o: app.h
graphics.o: graphics.h vec.h
ui.o: ui.h graphics.h
vec.o: vec.h

clean:
	rm *.o $(EXE)

.PHONY: clean
