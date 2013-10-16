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

void init(SDL_Window **w, SDL_Surface **s)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init failure : %s\n :(\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Create window
    *w = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( *w == NULL ) {
        fprintf(stderr, "SDL_CreateWindow failure : %s\n :(\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    //Get window surface
    *s = SDL_GetWindowSurface(*w);
}

void teardown(SDL_Window *w, SDL_Surface *s)
{
	//Deallocate surface
	SDL_FreeSurface(s);
	s = NULL;

	//Destroy window
	SDL_DestroyWindow(w);
	w = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Surface *surface = NULL;
    SDL_Event event;

    signal(SIGINT, sig_handler);

    init(&window, &surface);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);

    while (1) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            break;
        }
    }

    teardown(window, surface);

    return EXIT_SUCCESS;
}

