#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdint.h>
#include <image/image.h>
#ifdef TEST_BUILD
#include <SDL2/SDL.h>>

struct display_sdl_data_t {
    SDL_Window *window;
};
#else
#endif

union display_data_t {
    struct display_sdl_data_t sdl;
};

struct display_t {
    char *display_type_name;
    uint8_t display_type_id;
    union display_data_t data;
    uint16_t height;
    uint16_t width;
    uint8_t colour_type; // ENUM?
    uint32_t render_interval;
    uint32_t time_since_last_render;
    /* Buffer for static background elements (e.g. gauge face) */
    struct image_t background;
    /* Has static background? */
    uint8_t static_background_id;
};

struct display_type_t {
    const char *name;
    const void (*init)(struct display_t *display);
    const void (*write)(struct display_t *display);
};


/* Since font rendering is hard work, and making nice dial faces even harder
    User provides BMP
    BMP comes with 

    X,Y points for each point used to calculate angles


*/

#define DISPLAY_NOT_FOUND 0xFF
#define DISPLAY_NO_BACKGROUND 0x0

#define DISPLAY_DEF_BUFFERS(NAME, WIDTH, HEIGHT, BPP) uint8_t NAME##_buffer_data[WIDTH * HEIGHT * BPP];\
                                                      uint8_t NAME##_background_buffer_data[WIDTH * HEIGHT *BPP];
#define DISPLAY_DEF_STRUCT(NAME, WIDTH, HEIGHT, BPP) {NAME, DISPLAY_NOT_FOUND, NULL, WIDTH, HEIGHT, BPP, 0, 0, NULL, 0}

#define DISPLAY_TABLE_DEF(NAME, PREFIX) {NAME, PREFIX##_init, PREFIX##_write}
#define DISPLAY_TABLE_END() {NULL, NULL, NULL}

void display_init(struct display_t *display);

#endif

