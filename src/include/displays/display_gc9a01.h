#ifndef _DISPLAY_GC9A01_H
#define _DISPLAY_GC9A01_H

#include <displays/display.h>

void display_gc9a01_init(struct display *display);

void display_gc9a01_write(struct display_ *display, struct image *buffer);

#endif