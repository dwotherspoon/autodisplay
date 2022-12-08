#include <displays/display_sdl.h>
#include <stdio.h>

void display_sdl_init(struct display_t *display) {
    struct display_sdl_data_t *data = &display->data.sdl;

    data->window = SDL_CreateWindow("AutoDisplay Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        display->width, display->height, 0);
    if (data->window == NULL) {
        printf("Error: Failed to create window: %s\n", SDL_GetError());
    }
}

void display_sdl_write(struct display_t *display) {
}
