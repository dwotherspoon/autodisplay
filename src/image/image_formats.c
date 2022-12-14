#include <stddef.h>
#include <image/image_formats.h>

/* MONO 1 */
uint32_t image_format_mono1_convert_to_rgb888(uint32_t value) {
    return value == MONO_1_BLACK ? RGB_888_WHITE : RGB_888_BLACK;
}

uint32_t image_format_mono1_convert_from_rgb888(uint32_t value) {
    return value != RGB_888_BLACK ? MONO_1_WHITE : MONO_1_WHITE;
}

uint32_t image_format_mono1_get_pixel(struct image_t *image, uint16_t x, uint16_t y) {
    /* TODO: Implement this */
    return MONO_1_BLACK;
}

void image_format_mono1_set_pixel(struct image_t *image, uint16_t x, uint16_t y, uint32_t value) {
    /* TODO: Implement this */
}

/* MONO 8 */
uint32_t image_format_mono8_convert_to_rgb888(uint32_t value) {
    return RGB_888_BLACK;
}

uint32_t image_format_mono8_convert_from_rgb888(uint32_t value) {
    return MONO_8_BLACK;
}

uint32_t image_format_mono8_get_pixel(struct image_t *image, uint16_t x, uint16_t y) {
    /* TODO: Implement this */
    return MONO_8_BLACK;
}

void image_format_mono8_set_pixel(struct image_t *image, uint16_t x, uint16_t y, uint32_t value) {
    /* TODO: Implement this */
}

/* RGB 444 */
uint32_t image_format_rgb444_convert_to_rgb888(uint32_t value) {
    return RGB_888(RGB_444_R(value) << 4, RGB_444_G(value) << 4, RGB_444_B(value) << 4);
}

uint32_t image_format_rgb444_convert_from_rgb888(uint32_t value) {
    return RGB_444(RGB_888_R(value) >> 4, RGB_888_G(value) >> 4, RGB_888_B(value) >> 4);
}

uint32_t image_format_rgb444_get_pixel(struct image_t *image, uint16_t x, uint16_t y) {
    /* TODO: Implement this */
    return RGB_444_BLACK;
}

void image_format_rgb444_set_pixel(struct image_t *image, uint16_t x, uint16_t y, uint32_t value) {
    /* TODO: Implement this */
}

/* RGB 565 */
uint32_t image_format_rgb565_convert_to_rgb888(uint32_t value) {
    return RGB_888(RGB_565_R(value) << 3, RGB_565_G(value) << 2, RGB_565_B(value) << 3);
}

uint32_t image_format_rgb565_convert_from_rgb888(uint32_t value) {
    return RGB_565(RGB_888_R(value) >> 3, RGB_888_G(value) >> 2, RGB_888_B(value) >> 3);
}

uint32_t image_format_rgb565_get_pixel(struct image_t *image, uint16_t x, uint16_t y) {
    /* TODO: Implement this */
    return RGB_565_BLACK;
}

void image_format_rgb565_set_pixel(struct image_t *image, uint16_t x, uint16_t y, uint32_t value) {
    /* TODO: Implement this */
}

/* RGB 666 */
uint32_t image_format_rgb666_convert_to_rgb888(uint32_t value) {
    return RGB_888(RGB_666_R(value) << 2, RGB_666_G(value) << 2, RGB_666_B(value) << 2);
}

uint32_t image_format_rgb666_convert_from_rgb888(uint32_t value) {
    return RGB_666(RGB_888_R(value) >> 2, RGB_888_G(value) >> 2, RGB_888_B(value) >> 2);
}

uint32_t image_format_rgb666_get_pixel(struct image_t *image, uint16_t x, uint16_t y) {
    /* TODO: Implement this */
    return RGB_666_BLACK;
}

void image_format_rgb666_set_pixel(struct image_t *image, uint16_t x, uint16_t y, uint32_t value) {
    /* TODO: Implement this */
}

/* RGB 888 */
uint32_t image_format_rgb888_convert_to_rgb888(uint32_t value) {
    /* Nothing to do */
    return value;
}

uint32_t image_format_rgb888_convert_from_rgb888(uint32_t value) {
    /* Nothing to do */
    return value;
}

uint32_t image_format_rgb888_get_pixel(struct image_t *image, uint16_t x, uint16_t y) {
    /* TODO: Implement this */
    return RGB_888_BLACK;
}

void image_format_rgb888_set_pixel(struct image_t *image, uint16_t x, uint16_t y, uint32_t value) {
    /* TODO: Implement this */
}

struct image_format_t image_format_table[] = {
    IMAGE_FORMAT_TABLE_DEF("MONO1", 1, image_format_mono1),
    IMAGE_FORMAT_TABLE_DEF("MONO8", 8, image_format_mono8),
    IMAGE_FORMAT_TABLE_DEF("RGB444", 12, image_format_rgb444),
    IMAGE_FORMAT_TABLE_DEF("RGB565", 16, image_format_rgb565),
    IMAGE_FORMAT_TABLE_DEF("RGB666", 18, image_format_rgb666),
    IMAGE_FORMAT_TABLE_DEF("RGB888", 24, image_format_rgb888),
    IMAGE_FORMAT_TABLE_END()
};
