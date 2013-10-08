all: main


main: main.c
	gcc -o $@ $^ -lSDL

.PHONY: clean

clean:
	rm main *.o
