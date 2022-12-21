#include <displays/display_sdl.h>
#include <stdio.h>
#include <string.h>
#include <debug.h>
#include <global.h>

void display_sdl_init(struct display *display) {
    struct display_sdl_data *data = &display->data.sdl;

    data->window = SDL_CreateWindow("AutoDisplay Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    display->width, display->height, 0);
    ASSERT(data->window != NULL, "Error: Failed to create SDL window: %s\n", SDL_GetError());

    data->surface = SDL_CreateRGBSurface(0, display->width, display->height, 24, 0xff, 0xff00, 0xff0000, 0);
    ASSERT(data->surface != NULL, "ERROR: Failed to make SDL suface: %s\n", SDL_GetError());

    data->renderer = SDL_CreateRenderer(data->window, -1, 0);
}

void display_sdl_write(struct display *display, struct image *buffer) {
    SDL_Texture *tex;
    struct display_sdl_data *data = &display->data.sdl;
    memcpy(data->surface->pixels, buffer->data, display->width * display->height * 3);
    tex = SDL_CreateTextureFromSurface(data->renderer, data->surface);

    SDL_RenderClear(data->renderer);  //clear renderer for drawing
    SDL_RenderCopy(data->renderer, tex, NULL, NULL);
    SDL_RenderPresent(data->renderer);    //present renderer
}

void display_sdl_set_backlight(struct display *display, uint8_t value) {
    UNUSED(display);
    INFO("Set backlight to 0x%02x", value);
}
