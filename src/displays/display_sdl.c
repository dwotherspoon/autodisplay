#include <displays/display_sdl.h>
#include <stdio.h>
#include <string.h>

void display_sdl_init(struct display_t *display) {
    struct display_sdl_data_t *data = &display->data.sdl;

    data->window = SDL_CreateWindow("AutoDisplay Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        display->width, display->height, 0);
    if (data->window == NULL) {
        printf("Error: Failed to create window: %s\n", SDL_GetError());
    }
    data->surface = SDL_CreateRGBSurface(NULL, display->width, display->height, 24, 0xff, 0xff00, 0xff0000, 0);
    if (data->surface == NULL) {
        printf("ERROR: Failed to make suface: %s\n", SDL_GetError());
    }

    data->renderer = SDL_CreateRenderer(data->window, -1, 0);
}

void display_sdl_write(struct display_t *display) {
    SDL_Texture *tex;
    struct display_sdl_data_t *data = &display->data.sdl;
    memcpy(data->surface->pixels, display->buffer.data, display->width * display->height * 3);
    tex = SDL_CreateTextureFromSurface(data->renderer, data->surface);

    SDL_RenderClear(data->renderer);  //clear renderer for drawing
    SDL_RenderCopy(data->renderer, tex, NULL, NULL);
    SDL_RenderPresent(data->renderer);    //present renderer
}
