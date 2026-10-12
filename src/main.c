#include "wasm4.h"

#include "testimage.h"

void update () {
    *DRAW_COLORS = 2;
    text("Hello from C!", 10, 10);

    *DRAW_COLORS = 0x0234;
    blit(testimage, 64, 64, 16, 16, BLIT_2BPP);

    uint8_t gamepad = *GAMEPAD1;
    if (gamepad & BUTTON_1) {
        *DRAW_COLORS = 4;
    }

    text("Press X to blink", 16, 90);
}
