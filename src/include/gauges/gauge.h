#ifndef _GAUGE_H
#define _GAUGE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <config.h>
#include <displays/display.h>

/* Specific data types for gauges */

struct gauge_test_data {
    uint8_t dummy;
};

struct gauge_dial_data {
    uint8_t dummy;
};

union gauge_data {
    struct gauge_dial_data dial;
    struct gauge_test_data test;
};

struct gauge {
    const char type_name[LIMIT_TYPE_NAME_LEN];
    /* The id of the gauge type */
    struct gauge_type *type;
    uint8_t input_id;
    uint8_t font_id;
    bool imperial;
    uint8_t display_id;
    /* Sub-positioning on display, where used */
    uint8_t display_pos;
    /* Any extra data that the gauge needs to store */
    union gauge_data data;
    /* Order of drawing, 0 is first, 255 is last, allows layering gauges */
    /* Or do we get rid of this and just implicitly order them in config? */
    uint8_t draw_order;
};

struct gauge_type {
    const char name[LIMIT_TYPE_NAME_LEN];
    /* Pointer to function for rendering guage face */
    void (*render_face)(struct gauge *gauge, struct display *display);
    /* Pointer to function for rendering value */
    void (*render_value)(struct gauge *gauge, struct display *display);
};

#define GAUGE_TABLE_DEF(NAME, PREFIX) {NAME, PREFIX##_render_face, PREFIX##_render_value}
#define GAUGE_TABLE_END() {"", NULL, NULL}

/* */
extern struct gauge_type gauge_type_table[];

#endif
