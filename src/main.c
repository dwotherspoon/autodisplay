#include <debug.h>
#include <global.h>

bool init() {
    /* First flush the display buffers and show a splash screen */

    /* Pre-render display backgrounds/faces */

    /* This can be quite time consuming, since rotations are slow */


    /* Perform sweep animations for fun */
    return true;
}

int main() {
    INFO("SYSTEM START.\r\n");
    int a = 0;
    int b = 1;
    int c;

    c = a + b;

    /* After startup, Go to command processor */

    return c;
}