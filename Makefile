all: main


main: main.c
	gcc -g -o $@ $^ -lSDL2

.PHONY: clean

clean:
	rm main
