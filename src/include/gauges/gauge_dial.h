#ifndef _GAUGE_DIAL_H
#define _GAUGE_DIAL_H

#include <gauges/gauge.h>
#include <displays/display.h>

void gauge_dial_render_face(struct gauge *gauge, struct display *display);

void gauge_dial_render_value(struct gauge *gauge, struct display *display);

#endif
