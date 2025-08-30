#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "SDL_gamecontroller.h"
#include "SDL_timer.h"
#include "cube.h"
#include "rotation.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

const int16_t JOYSTICK_FACTOR = 2000;
const int16_t DEAD_ZONE_THRESHOLD = 16000 / JOYSTICK_FACTOR;

static inline float apply_deadzone(int16_t value, int16_t threshold) {
    if (abs(value) < threshold) {
        return 0.0f;
    }
    return value;
}

/*
 * initializes stuff in sdl.
 * fills the pointers to the window and renderer.
 * returns -1 in case of an error.
*/
int init_sdl(SDL_Window **win, SDL_Renderer **renderer, SDL_GameController **joystick) {

    // initialize sdl itself
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) == -1) return -1;

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

    *joystick = SDL_GameControllerOpen(0);
    if (*joystick == NULL) return -1; 

    return 0;
}

/* draws a cube on the screen */
void draw_cube(SDL_Renderer* renderer, cube* c) {
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff); // white

    // draw edges
    for (int i = 0 ; i < 12 ; i++) {
        float *v1 = c->vertices[EDGES_INDEXES[i][0]];
        float *v2 = c->vertices[EDGES_INDEXES[i][1]];

        SDL_RenderDrawLineF(renderer,
                         v1[0] + c->offset[0],
                         v1[1] + c->offset[1],
                         v2[0] + c->offset[0],
                         v2[1] + c->offset[1]);
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

    rotation_matrix rotation = rotation_matrix_new(M_PI / 200, M_PI / 120, M_PI / 80);
    cube c = cube_new(40, 400, 400);

    int joystick_leftx = 0;
    int joystick_lefty = 0;

    while(running) {
        // cap fps
        uint32_t start_time = SDL_GetTicks();

        // event loop
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;

            else if (e.type == SDL_CONTROLLERAXISMOTION) {
                if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) 
                    joystick_leftx = e.caxis.value / JOYSTICK_FACTOR;

                if (e.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) 
                    joystick_lefty = e.caxis.value / JOYSTICK_FACTOR;
            }
        }

        cube_wrap_offset_around_screen(&c, 800, 800);
        cube_translate_add(&c, apply_deadzone(joystick_leftx, DEAD_ZONE_THRESHOLD), apply_deadzone(joystick_lefty, DEAD_ZONE_THRESHOLD));
    
        draw_sdl(renderer, &c);

        uint32_t end_time = SDL_GetTicks();

        // cap framerate
        uint32_t delta = end_time - start_time;
        if (delta < SCREEN_TICKS_PER_FRAME)
            SDL_Delay(SCREEN_TICKS_PER_FRAME - delta);
    }
}

int main(int argc, char *argv[])
{
    SDL_Window* win;
    SDL_Renderer* renderer;
    SDL_GameController* joystick;

    if (init_sdl(&win, &renderer, &joystick) == -1) {
        printf("error with sdl initialization: %s", SDL_GetError());
        return -1;
    }

    // game loop
    gameloop(win, renderer);

    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_GameControllerClose(joystick);
    SDL_Quit();

    return 0;
}
