#include "wasm4.h"
#include "toolbar.h"
#include "testimage.h"
#include "item.h"
#include "helditem.h"
#include "click.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Toolbar *tb;
char message[] = "No item clicked";

void handleclick(struct toolbar *ctb, size_t item) {
    (void)ctb; // prevent unused parameter error
    strcpy(message, "Item 0 clicked");
    message[5] += item;

    if (helditem == NULL) {
        helditem = ctb->items[item];
        ctb->items[item] = NULL;
        flatten(ctb);
    } else {
        insert(ctb, helditem, item);
        helditem = NULL;
    }
};

void start() {
    tb = malloc(sizeof(Toolbar) + 8 * sizeof(Item*));
    *tb = (Toolbar){
        .side = RIGHT,

        .xpadding = 2,
        .ypadding = 2,
        .itempadding = 1,

        .imagew = ITEM_WIDTH,
        .imageh = ITEM_HEIGHT,

        .itemcount = 5,
        .maxitems = 8,
        .onclicked = &handleclick,
        .colors = 0x0021,
    };
    for (size_t i = 0; i < tb->itemcount; i++) {
        tb->items[i] = malloc(sizeof(Item));
        *tb->items[i] = (Item){
            .image = testimage,
            .colors = 0x0234,
            .hover_colors = 0x2344,
            .name = "Item",
        };
    }
}
void update() {
    *DRAW_COLORS = 2;
    text(message, 10, 10);

    *DRAW_COLORS = 0x0234;
    blit(testimage, 64, 64, 16, 16, BLIT_2BPP);

    drawtoolbar(tb);
    drawhelditem();

    updateclick();
}
