#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdint.h>
#include <stddef.h>

#include <config.h>
#include <image/image.h>
#ifdef TEST_BUILD
#include <SDL2/SDL.h>

struct display_sdl_data {
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Renderer* renderer;
};
#else
#endif

union display_data {
#ifdef TEST_BUILD
    struct display_sdl_data sdl;
#else
#endif
};

struct display_type {
    const char name[LIMIT_TYPE_NAME_LEN];
    void (*init)(struct display *display);
    void (*write)(struct display *display, struct image *buffer);
};

struct display {
    char type_name[LIMIT_TYPE_NAME_LEN];
    struct display_type *type;
    union display_data data;
    uint16_t width;
    uint16_t height;
    char image_format_name[LIMIT_TYPE_NAME_LEN];
    struct image_format *image_format;
    uint32_t render_interval;
    uint32_t time_since_last_render;
    /* Buffer for static background elements (e.g. gauge face) */
    struct image background;
    /* Has static background? */
    uint8_t static_background_id;
};


/* Since font rendering is hard work, and making nice dial faces even harder
    User provides BMP
    BMP comes with 

    X,Y points for each point used to calculate angles


*/

#define DISPLAY_NO_BACKGROUND 0x0

/* Size of buffer required for given size and bpp, rounded up */
#define DISPLAY_DEF_BG_BUFFER(NAME, WIDTH, HEIGHT, BPP) uint8_t NAME##_bg_buffer_data[IMAGE_BUFFER_SIZE(WIDTH, HEIGHT, BPP)];
#define DISPLAY_DEF_STRUCT(NAME, TYPE_NAME, WIDTH, HEIGHT, IMAGE_FORMAT_NAME) {TYPE_NAME, NULL, {0}, WIDTH, HEIGHT, IMAGE_FORMAT_NAME, NULL, 0, 0,\
                                                        IMAGE_DEF_STRUCT(WIDTH, HEIGHT, IMAGE_FORMAT_NAME, NAME##_bg_buffer_data), DISPLAY_NO_BACKGROUND}

#define DISPLAY_TABLE_DEF(NAME, PREFIX) {NAME, PREFIX##_init, PREFIX##_write}
#define DISPLAY_TABLE_END()             {"", NULL, NULL}

void display_init(struct display *display);
void display_render(struct display *display, uint8_t *data);

#endif
