#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdint.h>
#include <image/image.h>

struct display_t {
    uint16_t height;
    uint16_t width;
    uint8_t colour_type; // ENUM?
    uint8_t display_type; // ENUM?
    uint32_t render_interval;
    uint32_t time_since_last_render;
    /* Buffer for static background elements (e.g. gauge face) */
    image_t background;
    /* Has static background? */
    uint8_t static_background_id;

    void (*render_background)(struct display_t *display);
};

/* Note, display list is static, it may not change at runtime. */
extern struct display_t displays[];


/* Since font rendering is hard work, and making nice dial faces even harder
    User provides BMP
    BMP comes with 

    X,Y points for each point used to calculate angles


*/

#endif

