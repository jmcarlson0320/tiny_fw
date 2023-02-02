CC = clang
CFLAGS = -g -Wall -I/Users/jmc/devel/include -I/opt/homebrew/include
LIBS = -L/Users/jmc/devel/lib -L/opt/homebrew/lib -ltinyfw -lm -lsdl2
EXE = app

$(EXE): main.o gradient.o
	$(CC) -o $@ $^ $(LIBS)

main.o: gradient.h
gradient.o: gradient.h

run: $(EXE)
	./$(EXE)

clean:
	rm *.o $(EXE)

.PHONY: run clean
