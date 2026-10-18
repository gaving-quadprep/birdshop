#include "wasm4.h"
#include "pigeon.h"
#include "rectangle.h"
#include "toolbar.h"
#include "screwdriver.h"
#include "heatgun.h"
#include "item.h"
#include "mouse.h"
#include "framecnt.h"
#include "7segment.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Toolbar *tb;
Bird *current_bird;
char message[] = "No item clicked";

void handleclick(struct toolbar *ctb, size_t item) {
    strcpy(message, "Item 0 clicked");
    message[5] += item;

    if (helditem == NULL) {
        helditem = takeitem(ctb, item);
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
        .side = DOWN,

        .xpadding = 2,
        .ypadding = 2,
        .itempadding = 1,

        .imagew = 16,
        .imageh = 16,

        .itemcount = 5,
        .maxitems = 8,
        .onclicked = &handleclick,
        .colors = 0x0021,
    };
    for (size_t i = 0; i < tb->itemcount; i++) {
        tb->items[i] = malloc(sizeof(Item));
        *tb->items[i] = (Item) {
            .image = screwdriver,
            .imagetb = screwdriver,
			.dim = (Rect16) {0, 0, 16, 16},
            .colors = 0x4320,
            .hover_colors = 0x4432,
            .name = "Screwdriver",
        };
    }
	tb->items[1]->image = heatgun;
	tb->items[1]->imagetb = heatgun;
	tb->items[1]->name = "Heat Gun";

    current_bird = mkpigeon();
    current_bird->x = 64;
    current_bird->y = 64;
}
void update() {
    *DRAW_COLORS = 2;
    text(message, 10, 10);

    drawclock();
    drawbird(current_bird);
    drawtoolbar(tb);
    addspacer(tb);
    drawhelditem();

    updateclick();
	framecnt++;
}
