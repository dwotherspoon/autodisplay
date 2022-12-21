#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <debug.h>
#include <global.h>
#include <displays/display.h>
#include <image/image_formats.h>

DISPLAY_DEF_BG_BUFFER(win1, 240, 240, IMAGE_RGB888_BPP);
DISPLAY_DEF_BG_BUFFER(win2, 240, 240, IMAGE_RGB888_BPP);
DISPLAY_DEF_BG_BUFFER(win3, 240, 240, IMAGE_RGB888_BPP);

struct display displays[] = {
    DISPLAY_DEF_STRUCT(win1, "SDL", 240, 240, "RGB888"),
    DISPLAY_DEF_STRUCT(win2, "SDL", 240, 240, "RGB888"),
    DISPLAY_DEF_STRUCT(win3, "SDL", 240, 240, "RGB888")
};

uint8_t output_buffer[IMAGE_BUFFER_SIZE(240, 240, 24)];

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);
    bool quit = false;
    SDL_Event event;
    int res;

    INFO("Start");

    res = SDL_Init(SDL_INIT_VIDEO);
    ASSERT(res == 0, "Error: Failed to init SDL: %s\n", SDL_GetError());

    /* Start displays? */
    for (uint8_t id = 0; id < sizeof(displays)/sizeof(struct display); id++) {
        INFO("Start display %u", id);
        display_init(&displays[id]);
        INFO("Render display %u", id);
        display_render(&displays[id], output_buffer);
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
