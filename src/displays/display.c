#include <string.h>

#include <displays/display.h>
#include <image/image.h>
#include <debug.h>

#ifdef TEST_BUILD
#include <displays/display_sdl.h>
#else
#include <displays/display_gc9a01.h>
#endif

struct display_type_t display_table[] = {
#ifdef TEST_BUILD
    DISPLAY_TABLE_DEF("SDL", display_sdl),
#else
    DISPLAY_TABLE_DEF("GC9A01", display_gc9a01),
#endif
    DISPLAY_TABLE_END()
};

/** Find id of display in display table from name.
    @param name String, name of display to find.
    @return The id of the display in the table, or DISPLAY_NOT_FOUND (0xFF) on failure.
*/
uint8_t display_find_id(char *name) {
    uint8_t id;
    ASSERT(name != NULL, "Null input display name specified.");

    for (id = 0; display_table[id].name != NULL; id++) {
        if (strcmp(name, display_table[id].name) == 0) {
            return id;
        }
    }

    return DISPLAY_NOT_FOUND;
}

void display_init(struct display_t *display) {
    /* When a display is initialised, we need to match the type string to an id in the display table. */
    display->display_type_id = display_find_id(display->display_type_name);
    display_table[display->display_type_id].init(display);
}

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
