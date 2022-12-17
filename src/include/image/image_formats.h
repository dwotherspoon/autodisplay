#ifndef _IMAGE_FORMATS_H
#define _IMAGE_FORMATS_H

#include <stdint.h>
#include <image/image.h>

struct image_format {
    /* Type name to be referenced by other modules */
    char name[LIMIT_TYPE_NAME_LEN];
    /* Bits per pixel */
    uint8_t bpp;
    /* Function pointers */
    uint32_t (*convert_to_rgb888)(uint32_t value);
    uint32_t (*convert_from_rgb888)(uint32_t value);
    uint32_t (*get_pixel)(struct image *image, uint16_t x, uint16_t y);
    void (*set_pixel)(struct image *image, uint16_t x, uint16_t y, uint32_t value);
};

#define MONO_1_BLACK     (0x0)
#define MONO_1_WHITE     (0x1)

#define MONO_8_BLACK     (0x0)
#define MONO_8_WHITE     (0xFF)

#define RGB_444(R, G, B) ((R & 0xf) << 8 | (G & 0xf) << 4 | (B & 0xf))
#define RGB_444_R(V)     ((V >> 8) & 0xf)
#define RGB_444_G(V)     ((V >> 4) & 0xf)
#define RGB_444_B(V)     (V & 0xf)
#define RGB_444_BLACK    RGB_444(0, 0, 0)
#define RGB_444_WHITE    RGB_444(0xf, 0xf, 0xf)

#define RGB_565(R, G, B) ((R & 0x1f) << 11 | (G & 0x3f) << 5 | (B & 0x1f))
#define RGB_565_R(V)     ((V >> 11) & 0x1f)
#define RGB_565_G(V)     ((V >> 5) & 0x3f)
#define RGB_565_B(V)     (V & 0x1f)
#define RGB_565_BLACK    RGB_565(0, 0, 0)
#define RGB_565_WHITE    RGB_565(0x1f, 0x3f, 0x1f)

#define RGB_666(R, G, B) ((R & 0x3f) << 12 | (G & 0x3f) << 6 | (B & 0x3f))
#define RGB_666_R(V)     ((V >> 12) & 0x3f)
#define RGB_666_G(V)     ((V >> 6) & 0x3f)
#define RGB_666_B(V)     (V & 0x3f)
#define RGB_666_BLACK    RGB_666(0, 0, 0)
#define RGB_666_WHITE    RGB_666(0x3f, 0x3f, 0x3f)

#define RGB_888(R, G, B) ((R & 0xFF) << 16 | (G & 0xFF) << 8 | (B & 0xFF))
#define RGB_888_R(V)     ((V >> 16) & 0xff)
#define RGB_888_G(V)     ((V >> 8) & 0xff)
#define RGB_888_B(V)     (V & 0xff)
#define RGB_888_BLACK    RGB_888(0, 0, 0)
#define RGB_888_WHITE    RGB_888(0xff, 0xff, 0xff)
#define RGB_888_RED      RGB_888(0xff, 0, 0)
#define RGB_888_GREEN    RGB_888(0, 0xff, 0)
#define RGB_888_BLUE     RGB_888(0, 0, 0xff)

#define IMAGE_PIXEL_OFFSET(IMAGE, X, Y) ((Y) * (IMAGE)->width + (X))

#define IMAGE_FORMAT_TABLE_DEF(NAME, BPP, PREFIX) {NAME, BPP, PREFIX##_convert_to_rgb888, PREFIX##_convert_from_rgb888, PREFIX##_get_pixel, PREFIX##_set_pixel}
#define IMAGE_FORMAT_TABLE_END()                  {"", 0, NULL, NULL, NULL, NULL}

struct image_format *image_format_find(char *name);

#endif
