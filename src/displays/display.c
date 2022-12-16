#include <string.h>

#include <displays/display.h>
#include <image/image.h>
#include <debug.h>

#ifdef TEST_BUILD
#include <displays/display_sdl.h>
#else
#include <displays/display_gc9a01.h>
#endif

struct display_type_t display_type_table[] = {
#ifdef TEST_BUILD
    DISPLAY_TABLE_DEF("SDL", display_sdl),
#else
    DISPLAY_TABLE_DEF("GC9A01", display_gc9a01),
#endif
    DISPLAY_TABLE_END()
};

/** Find id of display type in display table from name.
    @param name String, name of display to find.
    @return The pointer to display type , or NULL on failure.
*/
struct display_type_t *display_find_type(char *name) {
    uint8_t id;
    ASSERT(name != NULL, "Null input display name specified.");

    for (id = 0; display_type_table[id].name[0] != 0; id++) {
        if (strcmp(name, display_type_table[id].name) == 0) {
            return &display_type_table[id];
        }
    }

    return NULL;
}

void display_init(struct display_t *display) {
    ASSERT(display != NULL, "Can not initialise NULL display.");
    /* When a display is initialised, we need to match the type string to an id in the display table. */
    display->type = display_find_type(display->type_name);
    display->type->init(display);
    /* We should also initalise the background and buffer */
    image_init(&display->background);
    image_init(&display->buffer);
}

void display_generate_background(struct display_t *display) {
    /* Is there a static background image for this display or do we fill it black? */

}

void display_render(struct display_t *display) {
    ASSERT(display != NULL);

    /* First we copy the pre-generated buffer in */
/*
    image_copy(&display->background, &buffer, 
                0, 0, display->width, display->height,
                0, 0, display->width, display->height);
    */

   image_draw_line(&display->buffer, 120, 0, 120, 240, RGB_888_RED, 1);

   display->type->write(display);

}
