#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <displays/display.h>

DISPLAY_DEF_BUFFERS(win1, 240, 240, 24);
DISPLAY_DEF_BUFFERS(win2, 240, 240, 24);
DISPLAY_DEF_BUFFERS(win3, 240, 240, 24);

struct display_t displays[] = {
    DISPLAY_DEF_STRUCT(win1, "SDL", 240, 240, 3),
    DISPLAY_DEF_STRUCT(win2, "SDL", 240, 240, 3),
    DISPLAY_DEF_STRUCT(win3, "SDL", 240, 240, 3)
};

int main(int argc, char *argv[]) {
    bool quit = false;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error: Failed to init SDL: %s\n", SDL_GetError());
        /* Print some error */
        return -1;
    }

    /* Start displays? */
    for (uint8_t id = 0; id < sizeof(displays)/sizeof(struct display_t); id++) {
        printf("Start display %u\n", id);
        display_init(&displays[id]);
    }

    while (!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_Delay(32);
    }

    return 0;
}
