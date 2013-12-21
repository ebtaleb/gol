FLAGS=-Wall -Wextra -Werror -pedantic -g -o

all: gol

gol: gol.c
	gcc $(FLAGS) $@ $^ -lSDL2 -std=gnu99

.PHONY: clean

clean:
	/bin/rm gol
