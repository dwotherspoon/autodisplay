#ifndef _GAUGE_TEST_H
#define _GAUGE_TEST_H

#include <gauges/gauge.h>
#include <displays/display.h>

void gauge_test_render_face(struct gauge *gauge, struct display *display);

void gauge_test_render_value(struct gauge *gauge, struct display *display);

#endif
