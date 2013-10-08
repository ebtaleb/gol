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
    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;
    SDL_Event event;

    signal(SIGINT, sig_handler);

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "SDL_Init failure : %s\n :(\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Hello gof!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow failure : %s\n :(\n", SDL_GetError());
        exit(EXIT_FAILURE);
    } else {
        surface = SDL_GetWindowSurface(window);
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
        SDL_UpdateWindowSurface(window);
        SDL_Delay(2000);
    }

    while (1) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            break;
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}

