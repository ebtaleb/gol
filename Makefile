all: main


main: main.c
	gcc -o $@ $^ -lSDL2

.PHONY: clean

clean:
	rm main
