#include <debug.h>
#include <global.h>


bool init() {
    /* Load the config from config address (FLASH) */

    /* Initialise displays */

    /* Initialise inputs */

    /* Initialise outputs */

    /* First flush the display buffers and show a splash screen */

    /* Pre-render display backgrounds/faces */

    /* This can be quite time consuming, since rotations are slow */

    /* Perform sweep animations for fun */

    return true;
}

int main() {
    INFO("SYSTEM START.\r\n");

    init();

    /* After startup, Go to command processor */

    return 0;
}