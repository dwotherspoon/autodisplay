#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdint.h>
#include <config.h>
#include <image/image_formats.h>

struct image {
    uint16_t width;
    uint16_t height;
    char format_name[LIMIT_TYPE_NAME_LEN];
    struct image_format *format;
    uint8_t *data;
};

void image_init(struct image *image);

void image_draw_line(struct image *image,
                        uint16_t start_x, uint16_t start_y,
                        uint16_t end_x, uint16_t end_y,
                        uint32_t colour, uint8_t thickness);

void image_draw_circle(struct image *image,
                        uint16_t centre_x, uint16_t centre_y,
                        uint16_t radius, uint32_t colour, uint8_t thickness);

void image_copy(struct image *src, struct image *dst,
                uint16_t src_x, uint16_t src_y, int16_t src_w, int16_t src_h,
                uint16_t dst_x, uint16_t dst_y, int16_t dst_w, int16_t dst_h);

#define IMAGE_BUFFER_SIZE(WIDTH, HEIGHT, BPP) (((WIDTH * HEIGHT * BPP) >> 3) + (((WIDTH * HEIGHT * BPP) & 0x7) ? 1 : 0))
#define IMAGE_DEF_STRUCT(WIDTH, HEIGHT, FORMAT_NAME, DATA) {WIDTH, HEIGHT, FORMAT_NAME, NULL, DATA}

#endif
