#include <display/display.h>
#include <image/image.h>
#include <debug.h>

void display_generate_background(struct display_t *display) {
    /* Is there a static background image for this display or do we fill it black? */

}

void display_render(struct display_t *display) {
    ASSERT(display != NULL);
    struct image_t buffer;

    /* First we copy the pre-generated buffer in */

    image_copy(&display->background, &buffer, 
                0, 0, display->width, display->height,
                0, 0, display->width, display->height);

}