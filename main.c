#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <SDL2/SDL.h>

void sig_handler(int signo)
{
    if (signo == SIGINT) {
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    signal(SIGINT, sig_handler);

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "SDL_Init failure : %s\n :(\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    while (1) {
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}

