#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

#define CASE_SIZE 20
#define HEIGHT 25
#define WIDTH 25

/*================================================================

    Just a little snake game, many things still need to be fixed
       and/or upgraded, but who cares? I have the big flemme.

  ================================================================*/

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
    grid[WIDTH * snHead->x + snHead->y] = snHead->dir;
    apply_movement(snHead);
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

int randint(int min, int max)
{
    /*
        Returns random number between min and max
    */
    return rand() / (RAND_MAX + 1.) * (max - min) + min;
}

void move_apple(SnDirection* grid, int apple[2])
{
    /*
        Move the apple to a new random position
    */
    apple[0] = randint(0, WIDTH);
    apple[1] = randint(0, HEIGHT);
    if (grid[WIDTH * apple[0] + apple[1]] != NONE)
        move_apple(grid, apple);
}

int check_hit_walls(SnDirection* grid, SnTip snHead)
{
    return snHead.x < 0 || snHead.y < 0 || snHead.x >= WIDTH || snHead.y >= HEIGHT;
}

int check_hit_itself(SnDirection* grid, SnTip snHead)
{
    return grid[WIDTH * snHead.x + snHead.y] != NONE;
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
            if (grid[WIDTH * x + y] != NONE)
            {
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
    SDL_Event event;

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
    
    // Initialize random number generation
    time_t t;
    if (time(&t) == (time_t)-1)
        goto Quit;
    srand((unsigned)t);

    // Create the snake game
    grid = malloc(sizeof(SnDirection) * HEIGHT * WIDTH); // The grid that contains the snake
    memset(grid, NONE, sizeof(SnDirection) * HEIGHT * WIDTH);
    SnTip snHead = { WIDTH / 2 + 2, HEIGHT / 2, LEFT }; // The tips of the snake
    SnTip snTail = { WIDTH / 2 + 7, HEIGHT / 2, LEFT };
    grid[WIDTH * snHead.x + snHead.y] = snHead.dir;
    int apple[2] = { WIDTH / 2 - 2, HEIGHT / 2 }; // The position of the apple

    // Game loop
    while (1)
    {
        // Manage key pressed
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                goto Quit;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_z && snHead.dir != DOWN)
                    snHead.dir = UP;
                else if (event.key.keysym.sym == SDLK_q && snHead.dir != RIGHT)
                    snHead.dir = LEFT;
                else if (event.key.keysym.sym == SDLK_s && snHead.dir != UP)
                    snHead.dir = DOWN;
                else if (event.key.keysym.sym == SDLK_d && snHead.dir != LEFT)
                    snHead.dir = RIGHT;
            }
        }

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
        if (check_hit_walls(grid, snHead) || check_hit_itself(grid, snHead))
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
