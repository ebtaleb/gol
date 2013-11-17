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

void init_display(SDL_Window **w, SDL_Renderer **r)
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

    int numcases_x = SCREEN_WIDTH / 21;
    int numcases_y = SCREEN_HEIGHT / 21;
    SDL_Rect *rect_array[numcases_y][numcases_x];
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;

    int **gol_array = (int **)malloc(sizeof(numcases_y));
    for (i = 0; i < numcases_x; i++) {
        gol_array[i] = (int *)malloc(sizeof(int)*numcases_x);
        memset(gol_array[i], 0, sizeof(int)*numcases_x);
    }

    Uint8 color[4] = {0, 0, 0, 0};

    for (i = 0; i < numcases_y; i++) {
        for (j = 0; j < numcases_x; j++) {
            rect_array[i][j] = (SDL_Rect *)malloc(sizeof(SDL_Rect));
            rect_array[i][j]->x = x;
            rect_array[i][j]->y = y;
            rect_array[i][j]->h = 20;
            rect_array[i][j]->w = 20;
            x += 21;
        }
        y += 21;
        x = 0;
    }

    signal(SIGINT, sig_handler);

    init_display(&window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

    for (i = 0; i < numcases_y; i++) {
        for (j = 0; j < numcases_x; j++) {
            SDL_RenderFillRect(renderer, rect_array[i][j]);
        }
    }

    SDL_RenderPresent(renderer);

    while (1) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            break;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            x = event.button.x / 21;
            y = event.button.y / 21;

            if (x < numcases_x && y < numcases_y) {

                if (gol_array[y][x] == 0) {
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
                    gol_array[y][x] = 1;
                } else {
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
                    gol_array[y][x] = 0;
                }

                SDL_RenderFillRect(renderer, rect_array[y][x]);
                SDL_RenderPresent(renderer);
            }
        }
    }

    teardown(window, renderer);

    return EXIT_SUCCESS;
}

