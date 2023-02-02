CC = gcc
CFLAGS = -g -Wall -I/Users/jmc/devel/include -I/opt/homebrew/include
LIBS = -L/Users/jmc/devel/lib -L/opt/homebrew/lib -ltinyfw -lm -lSDL2
EXE = app

$(EXE): main.o ui.o
	$(CC) -o $@ $^ $(LIBS)

ui.o: ui.h

run: $(EXE)
	./$(EXE)

clean:
	rm *.o $(EXE)

.PHONY: run clean
