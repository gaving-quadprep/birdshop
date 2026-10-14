#include "wasm4.h"
#include "toolbar.h"
#include "screwdriver.h"
#include "heatgun.h"
#include "item.h"
#include "helditem.h"
#include "mouse.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Toolbar *tb;
char message[] = "No item clicked";

void handleclick(struct toolbar *ctb, size_t item) {
    strcpy(message, "Item 0 clicked");
    message[5] += item;

    if (helditem == NULL) {
        helditem = take(ctb, item);
    } else {
        if (ctb->items[item] == NULL) {
            ctb->items[item] = helditem;
            helditem = NULL;
        }
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
            .image = screwdriver,
            .colors = 0x4320,
            .hover_colors = 0x4432,
            .name = "Screwdriver",
        };
    }
	tb->items[1]->image = heatgun;
	tb->items[1]->name = "Heat Gun";
}
void update() {
    *DRAW_COLORS = 2;
    text(message, 10, 10);

    drawtoolbar(tb);
    drawhelditem();
    checkplace(tb);

    updateclick();
}
