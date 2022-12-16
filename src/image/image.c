#include <image/image.h>
#include <debug.h>
#include <config.h>

void image_init(struct image_t *image) {
    ASSERT(image != NULL, "Can not init NULL image");
    image->format = image_format_find(image->format_name);
    ASSERT(image->format != NULL, "Can not find image format: %s", image->format_name);
}

uint32_t image_convert_pixel(uint32_t value, struct image_format_t *src_fmt, struct image_format_t *dst_fmt) {
    ASSERT(src_fmt != NULL, "Source format can not be NULL");
    ASSERT(dst_fmt != NULL, "Destination format can not be NULL");
    return dst_fmt->convert_from_rgb888(src_fmt->convert_to_rgb888(value));
}

uint32_t image_get_pixel(struct image_t *image, uint16_t x, uint16_t y, uint32_t value) {
    ASSERT(image != NULL, "Image can not be NULL\n");
    ASSERT(image->format != NULL, "Image format can not be NULL\n");
    return image->format->get_pixel(image, x, y);
}

void image_set_pixel(struct image_t *image, uint16_t x, uint16_t y, uint32_t value) {
    ASSERT(image != NULL, "Image can not be NULL\n");
    ASSERT(image->format != NULL, "Image format can not be NULL\n");
    image->format->set_pixel(image, x, y, value);
}

void image_draw_line(struct image_t *image,
                     uint16_t start_x, uint16_t start_y,
                     uint16_t end_x, uint16_t end_y,
                     uint32_t colour, uint8_t thickness) {
    if (start_x == end_x) {
        /* Straight line in y axis */
        if (start_y < end_y) {
            for (uint16_t y = start_y; y < end_y; y++) {
                /* TODO: Iterate over thickness */
                image_set_pixel(image, start_x, y, colour);
            }
             /* Draw the last pixel (avoid possible loop counter wrap-around) */
             /* TODO: Iterate over thickness */
             image_set_pixel(image, start_x, end_y, colour);
        } else {
            for (uint16_t y = end_y; y < start_y; y++) {
                /* TODO: Iterate over thickness */
                image_set_pixel(image, start_x, y, colour);
            }
            /* Draw the last pixel (avoid possible loop counter wrap-around) */
            /* TODO: Iterate over thickness */
            image_set_pixel(image, start_x, start_y, colour);
        }
    }
    else if (start_y == end_y) {
        /* Straight line in x axis */
        if (start_x < end_x) {
            for (uint16_t x = start_x; x < end_x; x++) {
                /* TODO: Iterate over thickness */
                image_set_pixel(image, x, start_y, colour);
            }
            /* Draw the last pixel (avoid possible loop counter wrap-around) */
            /* TODO: Iterate over thickness */
            image_set_pixel(image, end_x, start_y, colour);
        } else {
            for (uint16_t x = end_x; x < start_x; x++) {
                /* TODO: Iterate over thickness */
                image_set_pixel(image, x, start_y, colour);
            }
            /* Draw the last pixel (avoid possible loop counter wrap-around) */
            /* TODO: Iterate over thickness */
            image_set_pixel(image, start_x, start_y, colour);
        }
    } else {

    }
}

void image_copy(struct image_t *src, struct image_t *dst,
                uint16_t src_x, uint16_t src_y, int16_t src_w, int16_t src_h,
                uint16_t dst_x, uint16_t dst_y, int16_t dst_w, int16_t dst_h) {
    ASSERT(src->format == dst->format, "Images being copied should have the same format.");
    int16_t y, y_dec;
    /* Do widths match - no need to iterate over rows. */
    if (src_w == src->width && src_w == dst_w && src_w == dst->width) {

    } else {

    }
}
