#ifndef _GAUGE_H
#define _GAUGE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <config/limits.h>
#include <gauge/gauge_dial.h>
#include <gauge/gauge_test.h>

struct gauge_config_t {
    /* The id of the gauge type */
    uint8_t guage_type_id;
    uint8_t input_id;
    uint8_t font_id;
    bool imperial;
    uint8_t display_id;
    /* Sub-positioning on display, where used */
    uint8_t display_pos;
    /* Any extra data that the gauge needs to store */
    union data {
        struct gauge_dial_data_t dial;
        struct gauge_test_data_t test;
    };
    /* Order of drawing, 0 is first, 255 is last, allows layering gauges */
    /* Or do we get rid of this and just implicitly order them in config? */
    uint8_t draw_order;
};

struct gauge_type_t {
    char *name;
    /* Pointer to function for rendering guage face */
    void (*render_face)(struct gauge_config_t *config);
    /* Pointer to function for rendering value */
    void (*render_value)(struct gauge_config_t *config);
};

#define GAUGE_TABLE_DEF(NAME, PREFIX) {NAME, PREFIX##_render_face, PREFIX##_render_value}
#define GAUGE_TABLE_END() {NULL, NULL, NULL}
#define GAUGE_NOT_FOUND 0xFF

/* */
extern struct gauge_type_t gauge_type_table[];

struct gauge_config_t gauges[LIMIT_MAX_GAUGES];

uint8_t gauge_find_type_id(char *name);

#endif