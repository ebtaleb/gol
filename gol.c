#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void sig_handler(int signo)
{
    if (signo == SIGINT) {
        exit(0);
    }
}

void init(SDL_Window **w, SDL_Renderer **r)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init failure : %s\n :(\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *w = SDL_CreateWindow( "Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( *w == NULL ) {
        fprintf(stderr, "SDL_CreateWindow failure : %s\n :(\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    *r = SDL_CreateRenderer(*w, -1, SDL_RENDERER_ACCELERATED);
    if( *r == NULL ) {
        fprintf(stderr, "SDL_CreateRenderer failure : %s\n :(\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void teardown(SDL_Window *w, SDL_Renderer *r)
{
    SDL_DestroyRenderer(r);
	r = NULL;

	SDL_DestroyWindow(w);
	w = NULL;

	SDL_Quit();
}

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;

    signal(SIGINT, sig_handler);

    init(&window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_RenderDrawLine(renderer, 1, 240, 639, 240);
    SDL_RenderPresent(renderer);

    SDL_Delay(2000);

    while (1) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            break;
        }
    }

    teardown(window, renderer);

    return EXIT_SUCCESS;
}

