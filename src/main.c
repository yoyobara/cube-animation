#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct cube {
    int vertices[8][3];
} cube;

cube cube_new() {
    cube c;

    // fill vertices
    int index_counter = 0;
    for (int i = -1 ; i != 3 ; i += 2) 
        for (int j = -1 ; j != 3 ; j += 2)
            for (int k = -1 ; k != 3 ; k += 2) {
                c.vertices[index_counter][0] = i;
                c.vertices[index_counter][1] = j;
                c.vertices[index_counter][2] = k;
            }

    return c;
}

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

/*
 * draw the stuff on the screen
 * returns -1 in case of an error
 */
int draw_sdl(SDL_Renderer* renderer) {
    if (SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0xff) == -1)
        return -1;

    if (SDL_RenderClear(renderer) == -1) return -1;

    SDL_RenderPresent(renderer);
    return 0;
}

/*
 * returns -1 in case of an error
 */
int gameloop(SDL_Window* win, SDL_Renderer* renderer) {

    // game loop
    bool running = true;

    cube c = cube_new();
    
    while(running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
        }

        if (draw_sdl(renderer) == -1) return -1;
    }

    return 0;
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
    if (gameloop(win, renderer) == -1) {
        printf("error with sdl loop: %s", SDL_GetError());
        return -1;
    }

    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
