#include <stdio.h>
#include <SDL2/SDL.h>

#include "draw_functions.h"

void clear_screen(SDL_Renderer *ren)
{   
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);   
}

void draw_snake(SDL_Renderer *ren, int *snake, int sn_size)
{
    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
    for (int i = 0; i < sn_size * 2; i = i + 2)
    {
    	SDL_Rect rect = {
    		snake[i] * CASE_SIZE, snake[i+1] * CASE_SIZE,
    		CASE_SIZE, CASE_SIZE
    	};
        SDL_RenderFillRect(ren, &rect);
    }
}

void draw_apple(SDL_Renderer *ren, int apple[2])
{
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_Rect rect = {
        apple[0] * CASE_SIZE, apple[1] * CASE_SIZE,
        CASE_SIZE, CASE_SIZE
    };
    SDL_RenderFillRect(ren, &rect);
}