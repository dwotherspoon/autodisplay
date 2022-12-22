#include <debug.h>
#include <global.h>
#include <image/image.h>
#include <image/image_formats.h>
#include <displays/display.h>

DISPLAY_DEF_BG_BUFFER(disp1, 240, 240, IMAGE_RGB444_BPP);
DISPLAY_DEF_BG_BUFFER(disp2, 240, 240, IMAGE_RGB444_BPP);
DISPLAY_DEF_BG_BUFFER(disp3, 240, 240, IMAGE_RGB444_BPP);

struct display displays[] = {
    DISPLAY_DEF_STRUCT(disp1, "SDL", 240, 240, "RGB444"),
    DISPLAY_DEF_STRUCT(disp2, "SDL", 240, 240, "RGB444"),
    DISPLAY_DEF_STRUCT(disp3, "SDL", 240, 240, "RGB444")
};

uint8_t output_buffer[IMAGE_BUFFER_SIZE(240, 240, IMAGE_RGB444_BPP)];

void init() {
    /* Load the config from config address (FLASH) */

    /* Initialise displays */

    /* Initialise inputs */

    /* Initialise outputs */

    /* First flush the display buffers and show a splash screen */

    /* Pre-render display backgrounds/faces */

    /* This can be quite time consuming, since rotations are slow */

    /* Perform sweep animations for fun */

}

int main() {
    INFO("SYSTEM START.\r\n");

    init();

    /* After startup, Go to command processor */

    return 0;
}