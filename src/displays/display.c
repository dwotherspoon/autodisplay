#include <string.h>

#include <displays/display.h>
#include <image/image_formats.h>
#include <debug.h>

#ifdef TEST_BUILD
#include <displays/display_sdl.h>
#else
#include <displays/display_gc9a01a.h>
#endif

struct display_type display_type_table[] = {
#ifdef TEST_BUILD
    DISPLAY_TABLE_DEF("SDL", display_sdl),
#else
    DISPLAY_TABLE_DEF("GC9A01A", display_gc9a01a),
#endif
    DISPLAY_TABLE_END()
};

/** Find id of display type in display table from name.
    @param name String, name of display to find.
    @return The pointer to display type , or NULL on failure.
*/
struct display_type *display_find_type(char *name) {
    uint8_t id;
    ASSERT(name != NULL, "Null input display name specified.");

    for (id = 0; display_type_table[id].name[0] != 0; id++) {
        if (strcmp(name, display_type_table[id].name) == 0) {
            return &display_type_table[id];
        }
    }

    return NULL;
}

/** Initialise the display;
    @param name String, name of display to find.
    @return The pointer to display type , or NULL on failure.
*/
void display_init(struct display *display) {
    ASSERT(display != NULL, "Can not initialise NULL display.");
    /* When a display is initialised, we need to match the type string to an id in the display table. */
    display->type = display_find_type(display->type_name);
    display->type->init(display);
    /* We should also initalise the background and buffer */
    image_init(&display->background);
}

void display_generate_background(struct display *display) {
    /* Is there a static background image for this display or do we fill it black? */

}

/** Render a display.
    @param display The pointer to the display to render.
    @param data An area of scratch memory, to use to render the display.
*/
void display_render(struct display *display, uint8_t *data) {
    ASSERT(display != NULL, "Display can not be NULL.");
    ASSERT(data != NULL, "Data can not be NULL.");
    /* Note, we accept the display buffer as an argument,
       this allows sharing of the render buffer with all the displays.
       This reduces memory requirements. */
    struct image buffer = IMAGE_DEF_STRUCT(display->width, display->height, {0}, data);
    /* I don't like this, but I'm not sure of a better way. */
    memcpy(buffer.format_name, display->image_format_name, LIMIT_TYPE_NAME_LEN);
    image_init(&buffer);

    /* First we copy the pre-generated buffer in */
/*
    image_copy(&display->background, &buffer, 
                0, 0, display->width, display->height,
                0, 0, display->width, display->height);
    */

    image_draw_line(&buffer, 120, 0, 120, 240, IMAGE_RGB888_RED, 1);

    image_draw_line(&buffer, 240, 120 , 0, 120, IMAGE_RGB888_GREEN, 1);

    image_draw_line(&buffer, 0, 0 , 120, 120, IMAGE_RGB888_BLUE, 1);

    image_draw_circle(&buffer, 120, 120, 30, IMAGE_RGB888_BLUE, 1);

    image_draw_circle(&buffer, 120, 120, 99, IMAGE_RGB888_RED, 1);

    image_draw_circle(&buffer, 120, 120, 120, IMAGE_RGB888_GREEN, 1);

    image_fill_circle(&buffer, 60, 60, 30, IMAGE_RGB888(0, 128, 128));

    image_fill_rectangle(&buffer, 200, 200, 235, 235, IMAGE_RGB888(90, 90, 90));

    image_draw_rectangle(&buffer, 100, 100, 150, 170, IMAGE_RGB888_GREEN, 1);

    image_fill_rectangle(&buffer, 10, 15, 95, 70, IMAGE_RGB888_RED);

    /* Send the completed display buffer to the display */
    display->type->write(display, &buffer);
}
