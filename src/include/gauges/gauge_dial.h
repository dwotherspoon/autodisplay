#ifndef _GAUGE_DIAL_H
#define _GAUGE_DIAL_H

#include <gauges/gauge.h>
#include <displays/display.h>

void gauge_dial_render_face(struct gauge_t *gauge, struct display_t *display);

void gauge_dial_render_value(struct gauge_t *gauge, struct display_t *display);

#endif