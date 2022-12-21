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

#define IMAGE_MONO1_BLACK     (0x0)
#define IMAGE_MONO1_WHITE     (0x1)
#define IMAGE_MONO1_BPP       (1)

#define IMAGE_MONO8_BLACK     (0x0)
#define IMAGE_MONO8_WHITE     (0xFF)
#define IMAGE_MONO8_BPP       (8)

#define IMAGE_RGB444(R, G, B) ((R & 0xf) << 8 | (G & 0xf) << 4 | (B & 0xf))
#define IMAGE_RGB444_R(V)     ((V >> 8) & 0xf)
#define IMAGE_RGB444_G(V)     ((V >> 4) & 0xf)
#define IMAGE_RGB444_B(V)     (V & 0xf)
#define IMAGE_RGB444_BLACK    IMAGE_RGB444(0, 0, 0)
#define IMAGE_RGB444_WHITE    IMAGE_RGB444(0xf, 0xf, 0xf)
#define IMAGE_RGB444_RED      IMAGE_RGB444(0xf, 0, 0)
#define IMAGE_RGB444_GREEN    IMAGE_RGB444(0, 0xf, 0)
#define IMAGE_RGB444_BLUE     IMAGE_RGB444(0, 0, 0xf)
#define IMAGE_RGB444_BPP      (12)

#define IMAGE_RGB565(R, G, B) ((R & 0x1f) << 11 | (G & 0x3f) << 5 | (B & 0x1f))
#define IMAGE_RGB565_R(V)     ((V >> 11) & 0x1f)
#define IMAGE_RGB565_G(V)     ((V >> 5) & 0x3f)
#define IMAGE_RGB565_B(V)     (V & 0x1f)
#define IMAGE_RGB565_BLACK    IMAGE_RGB565(0, 0, 0)
#define IMAGE_RGB565_WHITE    IMAGERGB565(0x1f, 0x3f, 0x1f)
#define IMAGE_RGB565_RED      IMAGE_RGB565(0x1f, 0, 0)
#define IMAGE_RGB565_GREEN    IMAGE_RGB565(0, 0x3f, 0)
#define IMAGE_RGB565_BLUE     IMAGE_RGB565(0, 0, 0x1f)
#define IMAGE_RGB565_BPP      (16)

#define IMAGE_RGB666(R, G, B) ((R & 0x3f) << 12 | (G & 0x3f) << 6 | (B & 0x3f))
#define IMAGE_RGB666_R(V)     ((V >> 12) & 0x3f)
#define IMAGE_RGB666_G(V)     ((V >> 6) & 0x3f)
#define IMAGE_RGB666_B(V)     (V & 0x3f)
#define IMAGE_RGB666_BLACK    IMAGE_RGB666(0, 0, 0)
#define IMAGE_RGB666_WHITE    IMAGE_RGB666(0x3f, 0x3f, 0x3f)
#define IMAGE_RGB666_RED      IMAGE_RGB666(0x3f, 0, 0)
#define IMAGE_RGB666_GREEN    IMAGE_RGB666(0, 0x3f, 0)
#define IMAGE_RGB666_BLUE     IMAGE_RGB666(0, 0, 0x3f)
#define IMAGE_RGB666_BPP      (18)

#define IMAGE_RGB888(R, G, B) ((R & 0xFF) << 16 | (G & 0xFF) << 8 | (B & 0xFF))
#define IMAGE_RGB888_R(V)     ((V >> 16) & 0xff)
#define IMAGE_RGB888_G(V)     ((V >> 8) & 0xff)
#define IMAGE_RGB888_B(V)     (V & 0xff)
#define IMAGE_RGB888_BLACK    IMAGE_RGB888(0, 0, 0)
#define IMAGE_RGB888_WHITE    IMAGE_RGB888(0xff, 0xff, 0xff)
#define IMAGE_RGB888_RED      IMAGE_RGB888(0xff, 0, 0)
#define IMAGE_RGB888_GREEN    IMAGE_RGB888(0, 0xff, 0)
#define IMAGE_RGB888_BLUE     IMAGE_RGB888(0, 0, 0xff)
#define IMAGE_RGB888_BPP      (24)

#define IMAGE_PIXEL_OFFSET(IMAGE, X, Y) ((Y) * (IMAGE)->width + (X))

#define IMAGE_FORMAT_TABLE_DEF(NAME, BPP, PREFIX) {NAME, BPP, PREFIX##_convert_to_rgb888, PREFIX##_convert_from_rgb888, PREFIX##_get_pixel, PREFIX##_set_pixel}
#define IMAGE_FORMAT_TABLE_END()                  {"", 0, NULL, NULL, NULL, NULL}

struct image_format *image_format_find(char *name);

#endif
