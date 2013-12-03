#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

typedef struct {
    int x;
    int y;
} Point;

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

void init_grid(Point *numcases, SDL_Renderer *renderer, SDL_Rect ****rect_array)
{
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;

    *rect_array = (SDL_Rect ***)malloc(sizeof(SDL_Rect **)*numcases->y);

    for (i = 0; i < numcases->x; i++) {
        (*rect_array)[i] = (SDL_Rect **)malloc(sizeof(SDL_Rect *)*numcases->x);
    }

    for (i = 0; i < numcases->y; i++) {
        for (j = 0; j < numcases->x; j++) {
            (*rect_array)[i][j] = (SDL_Rect *)malloc(sizeof(SDL_Rect));
            (*rect_array)[i][j]->x = x;
            (*rect_array)[i][j]->y = y;
            (*rect_array)[i][j]->h = 20;
            (*rect_array)[i][j]->w = 20;
            x += 21;
        }
        y += 21;
        x = 0;
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

    for (i = 0; i < numcases->y; i++) {
        for (j = 0; j < numcases->x; j++) {
            SDL_RenderFillRect(renderer, (*rect_array)[i][j]);
        }
    }

    SDL_RenderPresent(renderer);
}

void init_gol_array(int **gol, Point *numcases)
{
    *gol = (int *)malloc(numcases->y * numcases->x * sizeof(int));
    memset(*gol, 0, sizeof(int)*numcases->x*numcases->y);
}

void update_grid(Point *cursor, Point *numcases, SDL_Renderer *renderer, int *gol_array, SDL_Rect ****rect_array)
{
    int x = cursor->x / 21;
    int y = cursor->y / 21;

    if (x < numcases->x && y < numcases->y) {

        int index = y*numcases->x + x;
        if (gol_array[index] == 0) {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
            gol_array[index] = 1;
        } else {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
            gol_array[index] = 0;
        }

        SDL_RenderFillRect(renderer, (*rect_array)[y][x]);
        SDL_RenderPresent(renderer);
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

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    Point numcases = {SCREEN_WIDTH / 21, SCREEN_HEIGHT / 21};
    Point cursor_coord = {0, 0};

    SDL_Rect ***rect_array = NULL;
    int *gol_array = NULL;

    signal(SIGINT, sig_handler);

    init_display(&window, &renderer);
    init_grid(&numcases, renderer, &rect_array);
    init_gol_array(&gol_array, &numcases);

    while (1) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            break;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            cursor_coord.x = event.button.x;
            cursor_coord.y = event.button.y;
            update_grid(&cursor_coord, &numcases, renderer, gol_array, &rect_array);
        }
    }

    teardown(window, renderer);

    return EXIT_SUCCESS;
}

