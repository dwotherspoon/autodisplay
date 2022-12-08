#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        /* Print some error */
        return -1;
    }
    
    SDL_Window *win1 = SDL_CreateWindow("Window 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 240, 240, 0);
    if (win1 == NULL) {
        return -1;
    }

    while (1) {
    }

    return 0;
}
