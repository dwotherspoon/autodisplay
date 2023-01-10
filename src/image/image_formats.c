#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include <image/image_formats.h>
#include <debug.h>

/* MISC */
uint32_t image_rgb888_to_luminance(uint32_t value) {
    /* Fixed point calculation for luminance:
       0.2989 ~= 76/255
       0.5870 ~= 150/255
       0.1140 ~= 29/255
       L = 0.2989R + 0.5870G + 0.1140B
       255L = 76R + 150G + 29B 
       Result in range 0 - 255
       Coefficents from OpenCV RGB2Gray */
    return (76 * IMAGE_RGB888_R(value) + 150 * IMAGE_RGB888_G(value) + 29 * IMAGE_RGB888_B(value)) / 255;
}

/* MONO 1 */
uint32_t image_mono1_convert_to_rgb888(uint32_t value) {
    return (value == IMAGE_MONO1_BLACK) ? IMAGE_RGB888_WHITE : IMAGE_RGB888_BLACK;
}

uint32_t image_mono1_convert_from_rgb888(uint32_t value) {
    uint32_t lum = image_rgb888_to_luminance(value);
    return (lum > 127) ? IMAGE_MONO1_WHITE : IMAGE_MONO1_BLACK;
}

uint32_t image_mono1_get_pixel(struct image *image, uint16_t x, uint16_t y) {
    ASSERT(image->data != NULL, "Image data can not be NULL");
    uint32_t offset = IMAGE_PIXEL_OFFSET(image, x, y);
    return (image->data[offset >> 3] >> (7 - (offset & 0x7))) & 0x1;
}

void image_mono1_set_pixel(struct image *image, uint16_t x, uint16_t y, uint32_t value) {
    ASSERT(image->data != NULL, "Image data can not be NULL");
    uint32_t offset = IMAGE_PIXEL_OFFSET(image, x, y);
    if (value) {
        /* Set bit */
        image->data[offset >> 3] |= 1 << (7 - (offset & 0x7));
    } else {
        /* Clear bit */
        image->data[offset >> 3] &= ~(1 << (7 - (offset & 0x7)));
    }
}

/* MONO 8 */
uint32_t image_mono8_convert_to_rgb888(uint32_t value) {
    return IMAGE_RGB888(value, value, value);
}

uint32_t image_mono8_convert_from_rgb888(uint32_t value) {
    return image_rgb888_to_luminance(value);
}

uint32_t image_mono8_get_pixel(struct image *image, uint16_t x, uint16_t y) {
    ASSERT(image->data != NULL, "Image data can not be NULL");
    uint32_t offset = IMAGE_PIXEL_OFFSET(image, x, y) ;
    return image->data[offset];
}

void image_mono8_set_pixel(struct image *image, uint16_t x, uint16_t y, uint32_t value) {
    ASSERT(image->data != NULL, "Image data can not be NULL");
    uint32_t offset = IMAGE_PIXEL_OFFSET(image, x, y);
    image->data[offset] = value;
}

/* RGB 444 */
uint32_t image_rgb444_convert_to_rgb888(uint32_t value) {
    return IMAGE_RGB888(IMAGE_RGB444_R(value) << 4,IMAGE_RGB444_G(value) << 4, IMAGE_RGB444_B(value) << 4);
}

uint32_t image_rgb444_convert_from_rgb888(uint32_t value) {
    return IMAGE_RGB444(IMAGE_RGB888_R(value) >> 4, IMAGE_RGB888_G(value) >> 4, IMAGE_RGB888_B(value) >> 4);
}

uint32_t image_rgb444_get_pixel(struct image *image, uint16_t x, uint16_t y) {
    ASSERT(image->data != NULL, "Image data can not be NULL");
    uint32_t offset = IMAGE_PIXEL_OFFSET(image, x, y) * 12;
    uint8_t byte1 = image->data[offset >> 3];
    uint8_t byte2 = image->data[(offset >> 3) + 1];
    /* Offset should always be 0x4 or 0x0 */
    ASSERT(!(offset & 0x3), "Unexpected offset 0x%x", offset);
    if (offset & 0x4) {
        /*  |    First Byte    |     Second Byte    |
            8         4       0/8         4         0      
            | X X X X | R R R R | G G G G | B B B B | */
        return IMAGE_RGB444(byte1 & 0x0f, (byte2 & 0xf0) >> 4, byte2 & 0x0f);
    } else {
        /*  |     First Byte    |    Second Byte    |
            8        4         0/8        4         0
            | R R R R | G G G G | B B B B | X X X X | */
        return IMAGE_RGB444((byte1 & 0xf0) >> 4, byte1 & 0x0f, (byte2 & 0xf0) >> 4);
    }
}

void image_rgb444_set_pixel(struct image *image, uint16_t x, uint16_t y, uint32_t value) {
    ASSERT(image->data != NULL, "Image data can not be NULL");
    uint32_t offset = IMAGE_PIXEL_OFFSET(image, x, y) * 12;
    /* Offset should always be 0x4 or 0x0 */
    ASSERT(!(offset & 0x3), "Unexpected offset 0x%x", offset);
    if (offset & 0x4) {
        /*  |    First Byte    |     Second Byte    |
            8         4       0/8         4         0      
            | X X X X | R R R R | G G G G | B B B B | */
        image->data[offset >> 3] = (image->data[offset >> 3] & 0xf0) | IMAGE_RGB444_R(value);
        image->data[(offset >> 3) + 1] = (IMAGE_RGB444_G(value) << 4) | IMAGE_RGB444_B(value);
    } else {
        /*  |     First Byte    |    Second Byte    |
            8        4         0/8        4         0
            | R R R R | G G G G | B B B B | X X X X | */
        image->data[offset >> 3] = (IMAGE_RGB444_R(value) << 4) | IMAGE_RGB444_G(value);
        image->data[(offset >> 3) + 1] = (IMAGE_RGB444_B(value) << 4) | (image->data[(offset >> 3) + 1] & 0x0f);
    }
}

/* RGB 565 */
uint32_t image_rgb565_convert_to_rgb888(uint32_t value) {
    return IMAGE_RGB888(IMAGE_RGB565_R(value) << 3, IMAGE_RGB565_G(value) << 2, IMAGE_RGB565_B(value) << 3);
}

uint32_t image_rgb565_convert_from_rgb888(uint32_t value) {
    return IMAGE_RGB565(IMAGE_RGB888_R(value) >> 3, IMAGE_RGB888_G(value) >> 2, IMAGE_RGB888_B(value) >> 3);
}

uint32_t image_rgb565_get_pixel(struct image *image, uint16_t x, uint16_t y) {
    ASSERT(image->data != NULL, "Image data can not be NULL");
    uint32_t offset = IMAGE_PIXEL_OFFSET(image, x, y) << 1;
    uint8_t byte1 = image->data[offset];
    uint8_t byte2 = image->data[offset + 1];
    /*  |    First Byte    |     Second Byte    |
        8         4       0/8         4         0      
        | R R R R | R G G G | G G G B | B B B B | */
    return IMAGE_RGB565((byte1 & 0xf8) >> 3, ((byte1 & 0x7) << 3) | ((byte2 & 0xe0) >> 5), byte2 & 0x1f);
}

void image_rgb565_set_pixel(struct image *image, uint16_t x, uint16_t y, uint32_t value) {
    ASSERT(image->data != NULL, "Image data can not be NULL");
    uint32_t offset = IMAGE_PIXEL_OFFSET(image, x, y) << 1;
    /*  |    First Byte    |     Second Byte    |
        8         4       0/8         4         0      
        | R R R R | R G G G | G G G B | B B B B | */
    image->data[offset] = (IMAGE_RGB565_R(value) << 3) | ((IMAGE_RGB565_G(value) & 0x38) >> 3);
    image->data[offset + 1] = ((IMAGE_RGB565_G(value) & 0x7) << 5) | (IMAGE_RGB565_B(value) & 0x1f);
}

/* RGB 666 */
uint32_t image_rgb666_convert_to_rgb888(uint32_t value) {
    return IMAGE_RGB888(IMAGE_RGB666_R(value) << 2, IMAGE_RGB666_G(value) << 2, IMAGE_RGB666_B(value) << 2);
}

uint32_t image_rgb666_convert_from_rgb888(uint32_t value) {
    return IMAGE_RGB666(IMAGE_RGB888_R(value) >> 2, IMAGE_RGB888_G(value) >> 2, IMAGE_RGB888_B(value) >> 2);
}

uint32_t image_rgb666_get_pixel(struct image *image, uint16_t x, uint16_t y) {
    ASSERT(image->data != NULL, "Image data can not be NULL");
    uint32_t offset = IMAGE_PIXEL_OFFSET(image, x, y) * 18;
    uint8_t byte1 = image->data[offset >> 3];
    uint8_t byte2 = image->data[(offset >> 3) + 1];
    uint8_t byte3 = image->data[(offset >> 3) + 2];
    /* Offset should always be 0x2 or 0x0 */
    ASSERT(!(offset & 0x5), "Unexpected offset 0x%x", offset);
    if (offset & 0x2) {
        /*  |    First Byte    |     Second Byte    |    Third Byte     |
            8         4       0/8         4        0/8        4         0
            | X X X X | X X R R | R R R R | G G G G | G G B B | B B B B | */
        return IMAGE_RGB666(((byte1 & 0x3) << 4) | ((byte2 & 0xf0) >> 4), 
                            ((byte2 & 0x0f) << 2) | ((byte3 & 0xc0) >> 6) ,
                            byte3 & 0x3f);
    } else {
        /*  |    First Byte    |     Second Byte    |    Third Byte     |
            8         4       0/8         4        0/8        4         0
            | R R R R | R R G G | G G G G | B B B B | B B X X | X X X X | */
        return IMAGE_RGB666((byte1 & 0xfc) >> 2,
                            ((byte1 & 0x3) << 4) | ((byte2 & 0xf0) >> 4),
                            ((byte2 & 0x0f) << 2) | ((byte3 & 0xc0) >> 6));
    }
}

void image_rgb666_set_pixel(struct image *image, uint16_t x, uint16_t y, uint32_t value) {
    ASSERT(image->data != NULL, "Image data can not be NULL");
    uint32_t offset = IMAGE_PIXEL_OFFSET(image, x, y) * 18;
    /* Offset should always be 0x2 or 0x0 */
    ASSERT(!(offset & 0x5), "Unexpected offset 0x%x", offset);
    if (offset & 0x2) {
        /*  |    First Byte    |     Second Byte    |    Third Byte     |
            8         4       0/8         4        0/8        4         0
            | X X X X | X X R R | R R R R | G G G G | G G B B | B B B B | */
        image->data[offset >> 3] = (image->data[offset >> 3] & 0xfc) | ((IMAGE_RGB666_R(value) & 0x30) >> 4);
        image->data[(offset >> 3) + 1] = ((IMAGE_RGB666_R(value) & 0x0f) << 4) | ((IMAGE_RGB666_G(value) & 0x3c) >> 2);
        image->data[(offset >> 3) + 2] = ((IMAGE_RGB666_G(value) & 0x03) << 6) | IMAGE_RGB666_B(value);
    } else {
        /*  |    First Byte    |     Second Byte    |    Third Byte     |
            8         4       0/8         4        0/8        4         0
            | R R R R | R R G G | G G G G | B B B B | B B X X | X X X X | */
        image->data[offset >> 3] = ((IMAGE_RGB666_R(value) & 0xf3) << 2) | ((IMAGE_RGB666_G(value) & 0x30) >> 4);
        image->data[(offset >> 3) + 1] = ((IMAGE_RGB666_G(value) & 0x0f) << 4) | ((IMAGE_RGB666_B(value) & 0x3c) << 2);
        image->data[(offset >> 3) + 2] = ((IMAGE_RGB666_B(value) & 0x03) << 6) | (image->data[(offset >> 3) + 2] & 0x3f);
    }
}

/* RGB 888 */
uint32_t image_rgb888_convert_to_rgb888(uint32_t value) {
    /* Nothing to do */
    return value;
}

uint32_t image_rgb888_convert_from_rgb888(uint32_t value) {
    /* Nothing to do */
    return value;
}

uint32_t image_rgb888_get_pixel(struct image *image, uint16_t x, uint16_t y) {
    ASSERT(image->data != NULL, "Image data can not be NULL");
    uint32_t offset = IMAGE_PIXEL_OFFSET(image, x, y) * 3;
    return IMAGE_RGB888(image->data[offset], image->data[offset + 1], image->data[offset + 2]);
}

void image_rgb888_set_pixel(struct image *image, uint16_t x, uint16_t y, uint32_t value) {
    ASSERT(image->data != NULL, "Image data can not be NULL");
    uint32_t offset = IMAGE_PIXEL_OFFSET(image, x, y) * 3;
    image->data[offset] = IMAGE_RGB888_R(value);
    image->data[offset + 1] = IMAGE_RGB888_G(value);
    image->data[offset + 2] = IMAGE_RGB888_B(value);
}

struct image_format image_format_table[] = {
    IMAGE_FORMAT_TABLE_DEF("MONO1", IMAGE_MONO1_BPP, image_mono1),
    IMAGE_FORMAT_TABLE_DEF("MONO8", IMAGE_MONO8_BPP, image_mono8),
    IMAGE_FORMAT_TABLE_DEF("RGB444", IMAGE_RGB444_BPP, image_rgb444),
    IMAGE_FORMAT_TABLE_DEF("RGB565", IMAGE_RGB565_BPP, image_rgb565),
    IMAGE_FORMAT_TABLE_DEF("RGB666", IMAGE_RGB666_BPP, image_rgb666),
    IMAGE_FORMAT_TABLE_DEF("RGB888", IMAGE_RGB888_BPP, image_rgb888),
    IMAGE_FORMAT_TABLE_END()
};

struct image_format *image_format_find(char *name) {
    uint8_t id;
    ASSERT(name != NULL, "Null input name specified.");
    for (id = 0; image_format_table[id].name[0] != 0; id++) {
        if (strcmp(name, image_format_table[id].name) == 0) {
            return &image_format_table[id];
        }
    }

    return NULL;
}
