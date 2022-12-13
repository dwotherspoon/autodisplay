#ifndef _IMAGE_FORMATS_H
#define _IMAGE_FORMATS_H

#include <stdint.h>
#include <image/image.h>

struct image_format_t {
    char name[LIMIT_TYPE_NAME_LEN];
    uint8_t bpp;
    uint32_t (*convert_to_rgb888)(uint32_t value);
    uint32_t (*convert_from_rgb888)(uint32_t value);
    uint32_t (*get_pixel)(struct image_t *image, uint16_t x, uint16_t y);
    void (*set_pixel)(struct image_t *image, uint16_t x, uint16_t y, uint32_t value);
};

#define MONO_1_BLACK (0x0)
#define MONO_1_WHITE (0x1)

#define MONO_8_BLACK (0x0)
#define MONO_8_WHITE (0xFF)

#define RGB_565(R, G, B) ((R & 0x1f) << 11 | (G & 0x3f) << 5 | (B & 0x1f))
#define RGB_565_R(V)     ((V >> 11) & 0x1f)
#define RGB_565_G(V)     ((V >> 5) & 0x3f)
#define RGB_565_B(V)     (V & 0x1f)
#define RGB_565_BLACK    RGB_565(0, 0, 0)
#define RGB_565_WHITE    RGB_565(0x1f, 0x3f, 0x1f)

#define RGB_888(R, G, B) ((R & 0xFF) << 16 | (G & 0xFF) << 8 | (B & 0xFF))
#define RGB_888_R(V)     ((V >> 16) & 0xff)
#define RGB_888_G(V)     ((V >> 8) & 0xff)
#define RGB_888_B(V)     (V & 0xff)
#define RGB_888_BLACK RGB_888(0, 0, 0)
#define RGB_888_WHITE RGB_888(0xFF, 0xFF, 0xFF)

#define IMAGE_FORMAT_TABLE_DEF(NAME, BPP, PREFIX) {NAME, BPP, PREFIX##_convert_to_rgb888, PREFIX##_convert_from_rgb888, PREFIX##_set_pixel, PREFIX##_get_pixel}
#define IMAGE_FORMAT_TABLE_END()                  {"", 0, NULL, NULL, NULL, NULL}

extern struct image_format_t image_format_table[];

#endif
