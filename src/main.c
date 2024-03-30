#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdbool.h>

const SDL_Color c();

/*
 * initializes stuff in sdl.
 * fills the pointers to the window and renderer.
 * returns -1 in case of an error.
*/
int init_sdl2(SDL_Window **win, SDL_Renderer **renderer) {

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

int main(int argc, char *argv[])
{
    SDL_Window* win;
    SDL_Renderer* renderer;
    init_sdl2(&win, &renderer);

    // game loop
    bool running = true;
    
    while(running) {
        SDL_RenderPresent(renderer);
    }
}
