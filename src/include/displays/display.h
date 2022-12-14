#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdint.h>

#include <config.h>
#include <image/image.h>
#ifdef TEST_BUILD
#include <SDL2/SDL.h>

struct display_sdl_data_t {
    SDL_Window *window;
};
#else
#endif

union display_data_t {
#ifdef TEST_BUILD
    struct display_sdl_data_t sdl;
#else
#endif
};

struct display_t {
    char type_name[LIMIT_TYPE_NAME_LEN];
    uint8_t type_id;
    union display_data_t data;
    uint16_t height;
    uint16_t width;
    char image_format_name[LIMIT_TYPE_NAME_LEN];
    struct image_format_t *image_format;
    uint32_t render_interval;
    uint32_t time_since_last_render;
    struct image_t buffer;
    /* Buffer for static background elements (e.g. gauge face) */
    struct image_t background;
    /* Has static background? */
    uint8_t static_background_id;
};

struct display_type_t {
    const char name[LIMIT_TYPE_NAME_LEN];
    void (*init)(struct display_t *display);
    void (*write)(struct display_t *display);
};


/* Since font rendering is hard work, and making nice dial faces even harder
    User provides BMP
    BMP comes with 

    X,Y points for each point used to calculate angles


*/

#define DISPLAY_NOT_FOUND 0xff
#define DISPLAY_NO_BACKGROUND 0x0

/* Size of buffer required for given size and bpp, rounded up */
#define DISPLAY_BUFFER_SIZE(WIDTH, HEIGHT, BPP) (((WIDTH * HEIGHT * BPP) >> 3) + (((WIDTH * HEIGHT * BPP) & 0x7) ? 1 : 0))
#define DISPLAY_DEF_BUFFERS(NAME, WIDTH, HEIGHT, BPP) uint8_t NAME##_buffer_data[DISPLAY_BUFFER_SIZE(WIDTH, HEIGHT, BPP)];\
                                                      uint8_t NAME##_bg_buffer_data[DISPLAY_BUFFER_SIZE(WIDTH, HEIGHT, BPP)]

#define DISPLAY_DEF_STRUCT(NAME, TYPE_NAME, WIDTH, HEIGHT, IMAGE_FORMAT) {TYPE_NAME, DISPLAY_NOT_FOUND, {0}, WIDTH, HEIGHT, IMAGE_FORMAT, 0, 0, 0,\
                                                        {WIDTH, HEIGHT, IMAGE_FORMAT, NAME##_buffer_data},\
                                                        {WIDTH, HEIGHT, IMAGE_FORMAT, NAME##_bg_buffer_data}, 0}

#define DISPLAY_TABLE_DEF(NAME, PREFIX) {NAME, PREFIX##_init, PREFIX##_write}
#define DISPLAY_TABLE_END()             {"", NULL, NULL}

void display_init(struct display_t *display);

#endif
