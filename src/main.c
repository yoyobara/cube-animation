#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>

#include "cube.h"


/*
 * initializes stuff in sdl.
 * fills the pointers to the window and renderer.
 * returns -1 in case of an error.
*/
int init_sdl(SDL_Window **win, SDL_Renderer **renderer) {

    // initialize sdl itself
    if (SDL_Init(SDL_INIT_VIDEO) == -1) return -1;

    // window
    *win = SDL_CreateWindow("cube animation",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 
                            800, 800,
                            0);
    if (*win == NULL) return -1;

    // renderer
    *renderer = SDL_CreateRenderer(*win, -1, 0);
    if (*renderer == NULL) return -1;

    return 0;
}

/* draws a cube on the screen */
void draw_cube(SDL_Renderer* renderer, cube* c) {
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff); // white

    // draw vertices
    for (int i = 0 ; i < 8 ; i++) {
        int *point = c->vertices[i];
        SDL_RenderDrawPoint(renderer, point[0], point[1]);
    }
}

/*
 * draw the stuff on the screen
 */
void draw_sdl(SDL_Renderer* renderer, cube* c) {
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0xff);
    SDL_RenderClear(renderer);

    draw_cube(renderer, c);

    SDL_RenderPresent(renderer);
}

/*
 */
void gameloop(SDL_Window* win, SDL_Renderer* renderer) {

    // game loop
    bool running = true;

    cube c = cube_new();
    
    while(running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
        }

        draw_sdl(renderer, &c);
    }
}

int main(int argc, char *argv[])
{
    SDL_Window* win;
    SDL_Renderer* renderer;
    if (init_sdl(&win, &renderer) == -1) {
        printf("error with sdl initialization: %s", SDL_GetError());
        return -1;
    }

    // game loop
    gameloop(win, renderer);

    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
