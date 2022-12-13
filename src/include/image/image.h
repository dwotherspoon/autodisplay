#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdint.h>

enum image_format_t {RGB_888 = 0, RGB_565, MONO_8, MONO_1};

struct image_t {
    uint16_t width;
    uint16_t height;
    enum image_format_t format;
    uint8_t *data;
};

void image_copy(struct image_t *src, struct image_t *dst,
                uint16_t src_x, uint16_t src_y, int16_t src_w, int16_t src_h,
                uint16_t dst_x, uint16_t dst_y, int16_t dst_w, int16_t dst_h);

#endif
