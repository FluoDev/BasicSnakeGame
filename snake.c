#include <stdio.h>
#include <SDL2/SDL.h>

#define CASE_SIZE 25
#define HEIGHT 20
#define WIDTH 20

/*
    Enum & Struct defintions
*/
typedef enum {
    UP,
    LEFT,
    RIGHT,
    DOWN,
    NONE
} SnDirection;

typedef struct T_SnakePart {
    int x, y;
    SnDirection dir;
} SnTip;

/*
    Game Functions defintions
*/
void apply_movement(SnTip* sn)
{
    if (sn->dir == UP)
    {
        sn->y = sn->y + -1;
    }
    else if
    (sn->dir == DOWN)
    {
        sn->y = sn->y + 1;
    }
    else if
    (sn->dir == LEFT)
    {
        sn->x = sn->x + -1;
    }
    else if
    (sn->dir == RIGHT)
    {
        sn->x = sn->x + 1;
    }
}

void move_snake(SnDirection* grid, SnTip* snHead, SnTip* snTail)
{
    // Move Head
    apply_movement(snHead);
    grid[WIDTH * snHead->x + snHead->y] = snHead->dir;
    // Move Tail
    grid[WIDTH * snTail->x + snTail->y] = NONE;
    apply_movement(snTail);
}

/*
    Drawing functions defintions
*/

void clear_screen(SDL_Renderer *ren)
{   
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);   
}

void draw_snake(SDL_Renderer *ren, SnDirection* grid)
{
    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            printf("%d %d %d\n", x, y, grid[WIDTH * x + y]);
            if (grid[WIDTH * x + y] == LEFT)
            {
                printf("%d %d\n", x, y);
                SDL_Rect rect = {
                    x * CASE_SIZE, y * CASE_SIZE,
                    CASE_SIZE, CASE_SIZE
                };
                SDL_RenderFillRect(ren, &rect);
            } 
        }
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

/*
    Main program part
*/
int main(void)
{
    SnDirection *grid = NULL;

    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        return 1;

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
    grid = malloc(sizeof(SnDirection) * HEIGHT * WIDTH);
    memset(grid, NONE, sizeof(SnDirection) * HEIGHT * WIDTH);
    SnTip snHead = { WIDTH / 2 + 2, HEIGHT / 2, LEFT };
    SnTip snTail = { WIDTH / 2 + 5, HEIGHT / 2, LEFT };
    int apple[2] = { WIDTH / 2 - 2, HEIGHT / 2 };

    // Game loop
    int going = 1;
    for (int i = 0; i < 7; ++i)
    {
        // Update game
        move_snake(grid, &snHead, &snTail);

        // Draw the game
        clear_screen(ren);
        draw_apple(ren, apple);
        draw_snake(ren, grid);
        SDL_RenderPresent(ren);

        SDL_Delay(500);
    }

    
    SDL_Delay(2000);
Quit:
    // Destroy, free and quit everything
    if (win != NULL)
        SDL_DestroyWindow(win);
    if (ren != NULL)
        SDL_DestroyRenderer(ren);

    if (grid != NULL)
        free(grid);

    SDL_Quit();
    return 0;
}
