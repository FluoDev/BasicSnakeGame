#ifndef DRAW_FUNC_H
#define DRAW_FUNC_H

#define CASE_SIZE 25

extern void clear_screen(SDL_Renderer *ren);
extern void draw_snake(SDL_Renderer *ren, int *snake, int sn_size);
extern void draw_apple(SDL_Renderer *ren, int apple[2]);

#endif