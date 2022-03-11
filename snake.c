#include <stdio.h>
#include <SDL2/SDL.h>

#include "draw_functions.h"

#define HEIGHT 400
#define WIDTH 500

int main(void)
{
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        goto Quit;

    // Create the window and the renderer
    SDL_Window *win = SDL_CreateWindow("- Basic Snake Game -",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       HEIGHT, WIDTH, 0);
    if (win == NULL)
        goto Quit;

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
    if (ren == NULL)
        goto Quit;

    // Create the snake game
    int snake_size = 3;
    int *snake = malloc(sizeof(int) * snake_size * 2);
    int apple[2] = { 0 };


    draw_snake(snake, snake_size);
    

Quit:
    // Destroy, free and quit everything
    if (win != NULL)
        SDL_DestroyWindow(win);
    if (ren != NULL)
        SDL_DestroyRenderer(ren);

    free(snake);

    SDL_Quit();
    return 0;
}
