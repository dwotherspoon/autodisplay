#include <stdlib.h>

#include <image/image.h>
#include <image/image_formats.h>
#include <debug.h>
#include <config.h>
#include <global.h>

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
        SWAP16(end_y, start_y);
    }
    ASSERT(start_y <= end_y, "Swap16 failed\n");
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
        SWAP16(end_x, start_x);
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
        SWAP16(end_x, start_x);
        SWAP16(end_y, start_y);
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
        SWAP16(start_x, end_x);
        SWAP16(start_y, end_y);
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

void image_draw_circle(struct image *image,
                        uint16_t centre_x, uint16_t centre_y,
                        uint16_t radius, uint32_t colour, uint8_t thickness) {
    /* Bresenham's circle algorithim */
    uint16_t x;
    uint16_t y = radius;
    int32_t d = 3 - 2 * radius;
    for (x = 0; x < y; x++) {
        image_set_pixel(image, centre_x + x, centre_y + y, colour);
        image_set_pixel(image, centre_x - x, centre_y + y, colour);
        image_set_pixel(image, centre_x + x, centre_y - y, colour);
        image_set_pixel(image, centre_x - x, centre_y - y, colour);
        image_set_pixel(image, centre_x + y, centre_y + x, colour);
        image_set_pixel(image, centre_x - y, centre_y + x, colour);
        image_set_pixel(image, centre_x + y, centre_y - x, colour);
        image_set_pixel(image, centre_x - y, centre_y - x, colour);
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
    image_set_pixel(image, centre_x + x, centre_y + y, colour);
    image_set_pixel(image, centre_x - x, centre_y + y, colour);
    image_set_pixel(image, centre_x + x, centre_y - y, colour);
    image_set_pixel(image, centre_x - x, centre_y - y, colour);
    image_set_pixel(image, centre_x + y, centre_y + x, colour);
    image_set_pixel(image, centre_x - y, centre_y + x, colour);
    image_set_pixel(image, centre_x + y, centre_y - x, colour);
    image_set_pixel(image, centre_x - y, centre_y - x, colour);
}

void image_draw_rectangle(struct image *image,
                            uint16_t x0, uint16_t y0,
                            uint16_t x1, uint16_t y1, uint32_t colour, uint8_t thickness) {
    image_draw_line_horizontal(image, x0, y0, x1, colour, thickness);
    image_draw_line_horizontal(image, x0, y1, x1, colour, thickness);
    image_draw_line_vertical(image, x0, y0, y1, colour, thickness);
    image_draw_line_vertical(image, x1, y0, y1, colour, thickness);
}

void image_fill_circle(struct image *image,
                        uint16_t centre_x, uint16_t centre_y,
                        uint16_t radius, uint32_t colour) {
    /* Bresenham's circle algorithim */
    uint16_t x;
    uint16_t y = radius;
    int32_t d = 3 - 2 * radius;
    for (x = 0; x < y; x++) {
        image_draw_line_horizontal(image, centre_x - x, centre_y + y, centre_x + x, colour, 1);
        image_draw_line_horizontal(image, centre_x - x, centre_y - y, centre_x + x, colour, 1);
        image_draw_line_horizontal(image, centre_x - y, centre_y + x, centre_x + y, colour, 1);
        image_draw_line_horizontal(image, centre_x - y, centre_y - x, centre_x + y, colour, 1);
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
    image_draw_line_horizontal(image, centre_x - x, centre_y + y, centre_x + x, colour, 1);
    image_draw_line_horizontal(image, centre_x - x, centre_y - y, centre_x + x, colour, 1);
    image_draw_line_horizontal(image, centre_x - y, centre_y + x, centre_x + y, colour, 1);
    image_draw_line_horizontal(image, centre_x - y, centre_y - x, centre_x + y, colour, 1);
}

void image_fill_rectangle(struct image *image,
                            uint16_t x0, uint16_t y0,
                            uint16_t x1, uint16_t y1, uint32_t colour) {
    uint16_t dx = abs(x0 - x1);
    uint16_t dy = abs(y0 - y1);
    uint16_t x;
    uint16_t y;
    /* Scan in the direction that results in the least calls to draw line */
    if (dx < dy) {
        /* Iterate over x */
        if (x0 > x1) {
            SWAP16(x0, x1);
            SWAP16(y0, y1);
        }
        for (x = x0; x < x1; x++) {
            image_draw_line_vertical(image, x, y0, y1, colour, 1);
        }

    } else {
        /* Iterate over y */
        if (y0 > y1) {
            SWAP16(x0, x1);
            SWAP16(y0, y1);
        }
        for (y = y0; y < y1; y++) {
            image_draw_line_horizontal(image, x0, y, x1, colour, 1);
        }
    }
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
