#ifndef _DISPLAY_SDL_H
#define _DISPLAY_SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <displays/display.h>

void display_sdl_init(struct display *display);

void display_sdl_write(struct display *display, struct image *buffer);

#endif
