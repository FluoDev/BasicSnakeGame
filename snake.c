#include <stdio.h>
#include <SDL2/SDL.h>

#define CASE_SIZE 20
#define HEIGHT 25
#define WIDTH 25

/*
    Enum & Struct defintions
*/
typedef enum {
    NONE,
    UP,
    LEFT,
    RIGHT,
    DOWN
} SnDirection;

typedef struct T_SnTip {
    int x, y;
    SnDirection dir;
} SnTip;

/*
    Game Functions defintions
*/
void apply_movement(SnTip* sn)
{
    /*
        Move a tip of the snake in the right direction
    */
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

void move_head(SnDirection* grid, SnTip* snHead)
{
    /*
        Move the head of the snake
    */
    apply_movement(snHead);
    grid[WIDTH * snHead->x + snHead->y] = snHead->dir;
}

void move_tail(SnDirection* grid, SnTip* snTail)
{
    /*
        Move the tail of the snake
    */
    grid[WIDTH * snTail->x + snTail->y] = NONE;
    apply_movement(snTail);
    if (grid[WIDTH * snTail->x + snTail->y] != NONE)
        snTail->dir = grid[WIDTH * snTail->x + snTail->y];
}

void move_apple(SnDirection* grid, int apple[2])
{
    /*
        Move the apple to a new random position
    */
   // TODO: Add random position
    apple[0] = 2; apple[1] = 2;
}

int check_hit_walls(SnDirection* grid, SnTip snHead)
{
    return snHead.x < 0 || snHead.y < 0 || snHead.x >= WIDTH || snHead.y >= HEIGHT;
}

/*
    Drawing functions defintions
*/
void clear_screen(SDL_Renderer *ren)
{   
    /*
        Clear the screen
    */
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);   
}

void draw_snake(SDL_Renderer *ren, SnDirection* grid)
{
    /*
        Draw the whole snake
    */
    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            // printf("%d %d %d\n", x, y, grid[WIDTH * x + y]);
            if (grid[WIDTH * x + y] != NONE)
            {
                // printf("%d %d\n", x, y);
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
    /*
        Draw the apple
    */
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
    grid = malloc(sizeof(SnDirection) * HEIGHT * WIDTH); // The grid that contains the snake
    memset(grid, NONE, sizeof(SnDirection) * HEIGHT * WIDTH);
    SnTip snHead = { WIDTH / 2 + 2, HEIGHT / 2, LEFT }; // The tips of the snake
    SnTip snTail = { WIDTH / 2 + 4, HEIGHT / 2, LEFT };
    grid[WIDTH * snHead.x + snHead.y] = snHead.dir;
    int apple[2] = { WIDTH / 2 - 2, HEIGHT / 2 }; // The position of the apple

    // Game loop
    while (1)
    {
        // Update game
        move_head(grid, &snHead);
        if (snHead.x == apple[0] && snHead.y == apple[1])
        {
            move_apple(grid, apple);
        }
        else
        {
            move_tail(grid, &snTail);
        }

        // Check end
        if (check_hit_walls(grid, snHead))
        {
            break;
        }        

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
