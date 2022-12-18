#include <image/image.h>
#include <debug.h>
#include <config.h>
#include <global.h>
#include <stdlib.h>

void image_init(struct image *image) {
    ASSERT(image != NULL, "Can not init NULL image");
    image->format = image_format_find(image->format_name);
    ASSERT(image->format != NULL, "Can not find image format: %s", image->format_name);
}

uint32_t image_convert_pixel(uint32_t value, struct image_format *src_fmt, struct image_format *dst_fmt) {
    ASSERT(src_fmt != NULL, "Source format can not be NULL");
    ASSERT(dst_fmt != NULL, "Destination format can not be NULL");
    return dst_fmt->convert_from_rgb888(src_fmt->convert_to_rgb888(value));
}

uint32_t image_get_pixel(struct image *image, uint16_t x, uint16_t y, uint32_t value) {
    ASSERT(image != NULL, "Image can not be NULL\n");
    ASSERT(image->format != NULL, "Image format can not be NULL\n");
    return image->format->get_pixel(image, x, y);
}

void image_set_pixel(struct image *image, uint16_t x, uint16_t y, uint32_t value) {
    ASSERT(image != NULL, "Image can not be NULL\n");
    ASSERT(image->format != NULL, "Image format can not be NULL\n");
    image->format->set_pixel(image, x, y, value);
}

void image_draw_line_vertical(struct image *image,
                                uint16_t x, uint16_t start_y,
                                uint16_t end_y, uint32_t colour, uint8_t thickness) {
    /* Note: could be optimised further at the image format level. */
    /* Straight line in y axis */
    if (end_y < start_y) {
        SWAP(end_y, start_y);
    }
    ASSERT(start_y <= end_y, "Swap failed\n");
    for (uint16_t y = start_y; y < end_y; y++) {
        /* TODO: Iterate over thickness */
        image_set_pixel(image, x, y, colour);
    }
    /* Draw the last pixel (avoid possible loop counter wrap-around) */
    /* TODO: Iterate over thickness */
    image_set_pixel(image, x, end_y, colour);
}

void image_draw_line_horizontal(struct image *image,
                                uint16_t start_x, uint16_t y,
                                uint16_t end_x, uint32_t colour, uint8_t thickness) {
    /* Note: could be optimised further at the image format level. */
    /* Straight line in x axis */
    if (end_x < start_x) {
        SWAP(end_x, start_x);
    }
    for (uint16_t x = start_x; x < end_x; x++) {
        /* TODO: Iterate over thickness */
        image_set_pixel(image, x, y, colour);
    }
    /* Draw the last pixel (avoid possible loop counter wrap-around) */
    /* TODO: Iterate over thickness */
    image_set_pixel(image, end_x, y, colour);
}

void image_draw_line_low(struct image *image,
                            uint16_t start_x, uint16_t start_y,
                            uint16_t end_x, uint16_t end_y,
                            uint32_t colour, uint8_t thickness) {
    if (start_x > end_x) {
        SWAP(end_x, start_x);
        SWAP(end_y, start_y);
    }
    int32_t dx  = end_x - start_x;
    int32_t dy = end_y - start_y;
    uint16_t y = start_y;
    uint16_t x;
    int16_t yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int32_t d = (2 * dy) - dx;

    for (x = start_x; x < end_x; x++) {
        image_set_pixel(image, x, y, colour);
        if (d > 0) {
            y = y + yi;
            d = d + (2 * (dy - dx));
        } else {
            d = d + 2 * dy;
        }
    }
}

void image_draw_line_high(struct image *image,
                        uint16_t start_x, uint16_t start_y,
                        uint16_t end_x, uint16_t end_y,
                        uint32_t colour, uint8_t thickness) {
    if (start_y > end_y) {
        SWAP(start_x, end_x);
        SWAP(start_y, end_y);
    }
    int32_t dx = end_x - start_x;
    int32_t dy = end_y - start_y;
    uint16_t x = start_x;
    uint16_t y;
    int16_t xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int32_t d = (2 * dx) - dy;

    for (y = start_y; y < end_y; y++) {
        image_set_pixel(image, x, y, colour);
        if (d > 0) {
            x = x + xi;
            d = d + (2 * (dx - dy));
        } else {
            d = d + 2 * dx;
        }
    }
}

void image_draw_line(struct image *image,
                        uint16_t start_x, uint16_t start_y,
                        uint16_t end_x, uint16_t end_y,
                        uint32_t colour, uint8_t thickness) {
    /* Implementations for x and y lines could be optimised further at the image format level */
    if (start_x == end_x) {
        /* Straight line in y axis */
        image_draw_line_vertical(image, start_x, start_y, end_y, colour, thickness);
    }
    else if (start_y == end_y) {
        /* Straight line in x axis */
        image_draw_line_horizontal(image, start_x, start_y, end_x, colour, thickness);
    } else {
        /* Diagonal lines - Bresenham's algorithim */
        if (abs(end_y - start_y) < abs(end_x - start_x)) {
            image_draw_line_low(image, start_x, start_y, end_x, end_y, colour, thickness);
        } else {
            image_draw_line_high(image, start_x, start_y, end_x, end_y, colour, thickness);
        }
    }
}

void image_draw_line_aliased(struct image *image,
                                uint16_t start_x, uint16_t start_y,
                                uint16_t end_x, uint16_t end_y,
                                uint32_t colour, uint8_t thickness) {
    /* Use Xiaolin Wu's line algorithm */
}

void image_copy(struct image *src, struct image *dst,
                uint16_t src_x, uint16_t src_y, int16_t src_w, int16_t src_h,
                uint16_t dst_x, uint16_t dst_y, int16_t dst_w, int16_t dst_h) {
    ASSERT(src->format == dst->format, "Images being copied should have the same format.");
    int16_t y, y_dec;
    /* Do widths match - no need to iterate over rows. */
    if (src_w == src->width && src_w == dst_w && src_w == dst->width) {

    } else {

    }
}
