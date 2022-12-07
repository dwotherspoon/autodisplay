#ifndef _GAUGE_TEST_H
#define _GAUGE_TEST_H

#include <gauge/gauge.h>
#include <display/display.h>

struct gauge_test_data_t {
    uint8_t dummy;
};

void gauge_test_render_face(struct gauge_config_t *config, struct display_t *display);

void gauge_test_render_value(struct gauge_config_t *config, struct display_t *display);

#endif