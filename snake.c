#include <stdio.h>
#include <SDL2/SDL.h>

#include "draw_functions.h"

#define HEIGHT 20
#define WIDTH 20

int main(void)
{
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        goto Quit;

    // Create the window and the renderer
    SDL_Window *win = SDL_CreateWindow("- Basic Snake Game -",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       HEIGHT * CASE_SIZE,
                                       WIDTH * CASE_SIZE, 0);
    if (win == NULL)
        goto Quit;

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
    if (ren == NULL)
        goto Quit;

    // Create the snake game
    int snake_size = 3;
    int *snake = malloc(sizeof(int) * snake_size * 2);
    for (int i = 0; i < snake_size * 2; i = i + 2)
    {
        snake[i] = WIDTH / 2 + 2 + i / 2;
        snake[i+1] = HEIGHT / 2;
    }
    int apple[2] = { WIDTH / 2 - 3, HEIGHT / 2 };

    int going = 1;
    while (going)
    {
        draw_snake(ren, snake, snake_size);
        draw_apple(ren, apple);
        SDL_RenderPresent(ren);

        

        SDL_Delay(250);
        break;
    }

    
    SDL_Delay(2000);
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
