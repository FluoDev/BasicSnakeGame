#include <stdio.h>
#include <SDL2/SDL.h>

#include "draw_functions.h"

#define HEIGHT 20
#define WIDTH 20

int *copy_list(int *list, int size)
{
    /*
        Copy a int list into another one.
    */
    int *res = malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i)
    {
        res[i] = list[i];
    }
    return res;
}

void snake_move(int *snake, int sn_size, int dir[2])
{
    /*
        Make the snake move in the right direction.
    */
    int *old_sn = copy_list(snake, sn_size * 2);
    snake[0] = old_sn[0] + dir[0]; snake[1] = old_sn[1] + dir[1]; 
    for (int i = 0; i < sn_size * 2 - 2; i = i + 2)
    {
        snake[2 + i] = old_sn[i];
        snake[2 + i + 1] = old_sn[i + 1];
    }
    free(old_sn);
}


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
    int direction[2] = { -1, 0 };


    // Game loop
    int going = 1;
    for (int i = 0; i < 5; ++i)
    {
        // Draw the game
        clear_screen(ren);
        draw_apple(ren, apple);
        draw_snake(ren, snake, snake_size);
        SDL_RenderPresent(ren);

        snake_move(snake, snake_size, direction);

        SDL_Delay(250);
    }

    
    SDL_Delay(2000);
Quit:
    // Destroy, free and quit everything
    if (win != NULL)
        SDL_DestroyWindow(win);
    if (ren != NULL)
        SDL_DestroyRenderer(ren);

    if (snake != NULL)
        free(snake);

    SDL_Quit();
    return 0;
}
