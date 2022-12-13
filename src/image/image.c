#include <image/image.h>
#include <debug.h>
#include <config.h>

/* N.B. what about 1BPP greyscale? */

#define PIXEL_PTR(IMAGE, X, Y) ((IMAGE)->data + ((((((IMAGE)->width * (Y)) + (X)) * image_format_bpp_lut[(IMAGE)->format])) >> 3))

uint32_t image_convertpixel(uint32_t value, struct image_format_t *src_fmt, struct image_format_t *dst_fmt) {
    /* First convet the pixel into RGB 888 then to destination format? */
    return -1;
}

void image_setpixel(struct image_t *image, uint16_t x, uint16_t y, uint32_t value) {

}

void image_drawline(struct image_t *image,
                    uint16_t start_x, uint16_t start_y,
                    uint16_t end_x, uint16_t end_y,
                    uint32_t colour, uint8_t thickness) {
    if (start_x == end_x) {
        /* Straight line in y axis */
        if (start_y < end_y) {
            for (uint16_t y = start_y; y < end_y; y++) {
                /* TODO: Iterate over thickness */
                image_setpixel(image, start_x, y, colour);
            }
             /* Draw the last pixel (avoid possible loop counter wrap-around) */
             /* TODO: Iterate over thickness */
             image_setpixel(image, start_x, end_y, colour);
        } else {
            for (uint16_t y = end_y; y < start_y; y++) {
                /* TODO: Iterate over thickness */
                image_setpixel(image, start_x, y, colour);
            }
            /* Draw the last pixel (avoid possible loop counter wrap-around) */
            /* TODO: Iterate over thickness */
            image_setpixel(image, start_x, start_y, colour);
        }
    }
    else if (start_y == end_y) {
        /* Straight line in x axis */
        if (start_x < end_x) {
            for (uint16_t x = start_x; x < end_x; x++) {
                /* TODO: Iterate over thickness */
                image_setpixel(image, x, start_y, colour);
            }
            /* Draw the last pixel (avoid possible loop counter wrap-around) */
            /* TODO: Iterate over thickness */
            image_setpixel(image, end_x, start_y, colour);
        } else {
            for (uint16_t x = end_x; x < start_x; x++) {
                /* TODO: Iterate over thickness */
                image_setpixel(image, x, start_y, colour);
            }
            /* Draw the last pixel (avoid possible loop counter wrap-around) */
            /* TODO: Iterate over thickness */
            image_setpixel(image, start_x, start_y, colour);
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
