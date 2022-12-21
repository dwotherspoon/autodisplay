#ifndef _DISPLAY_GC9A01A_H
#define _DISPLAY_GC9A01A_H

#include <displays/display.h>

void display_gc9a01a_init(struct display *display);

void display_gc9a01a_write(struct display *display, struct image *buffer);

void display_gc9a01a_set_backlight(struct display *display, uint8_t value);

/* */
#define GC9A01A_CMD_DISPLAY_ID 0x04
#define GC9A01A_CMD_DISPLAY_STATUS 0x09
#define GC9A01A_CMD_ENTER_SLEEP 0x10
#define GC9A01A_CMD_EXIT_SLEEP 0x11
#define GC9A01A_CMD_ENTER_PARTIAL 0x12
#define GC9A01A_CMD_ENTER_NORMAL 0x13

#endif