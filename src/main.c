#include "wasm4.h"
#include "toolbar.h"
#include "testimage.h"
#include <stddef.h>
#include <stdlib.h>

struct toolbar *tb;

void start() {
    tb = malloc(sizeof(struct toolbar) + 5 * sizeof(struct tbentry));
    *tb = (struct toolbar){
        .xpadding = 3,
        .ypadding = 2,
        .itempadding = 1,

        .imagew = 16,
        .imageh = 16,

        .itemcount = 5,
    };
    for (size_t i = 0; i < tb->itemcount; i++) {
        tb->items[i] = (struct tbentry){
            .image = testimage,
            .colors = 0x0234,
            .hover_colors = 0x2344,
            .name = "Item",
            .onclicked = NULL,
        };
    }
}
void update() {
    *DRAW_COLORS = 2;
    text("Hello from C!", 10, 10);

    *DRAW_COLORS = 0x0234;
    blit(testimage, 64, 64, 16, 16, BLIT_2BPP);

    draw_toolbar(tb);
}
