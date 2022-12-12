#include <image/image.h>
#include <debug.h>

uint8_t image_format_pixel_size_lut;

#define GET_PIXEL(image_t)


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
