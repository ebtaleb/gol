all: gol


gol: gol.c
	gcc -g -o $@ $^ -lSDL2

.PHONY: clean

clean:
	rm gol
