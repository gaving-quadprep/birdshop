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
#include "workspace.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char m[] = "Use a heat gun to\nloosen the adhesive\non the head             ";

void start() {
    wksp = malloc(sizeof(Workspace));

    wksp->message = m;
    wksp->prog = 0;

    wksp->items = mkitemlist(8);
    Toolbar *tb = malloc(sizeof(Toolbar) + 8 * sizeof(Item*));
    *tb = (Toolbar){
        .side = DOWN,

        .xpadding = 2,
        .ypadding = 2,
        .itempadding = 1,

        .imagew = 16,
        .imageh = 16,

        .itemcount = 2,
        .maxitems = 8,
        .onclicked = &handleclick,
        .colors = 0x0021,
    };
    tb->items[0] = malloc(sizeof(Item));
    *tb->items[0] = (Item) {
        .image = screwdriver,
        .imagetb = screwdriver,
        .dim = (Rect16) {0, 0, 16, 16},
        .colors = 0x4320,
        .hover_colors = 0x4432,
        .name = "Screwdriver",
        .id = 1,
    };
    tb->items[1] = malloc(sizeof(Item));
    *tb->items[1] = (Item) {
        .image = heatgun,
        .imagetb = heatgun,
        .dim = (Rect16) {0, 0, 16, 16},
        .colors = 0x4320,
        .hover_colors = 0x4432,
        .name = "Heat Gun",
        .id = 2,
    };

    wksp->tb = tb;

    wksp->bird = mkpigeon();
    wksp->bird->x = 64;
    wksp->bird->y = 64;
}
void update() {

    drawworkspace(wksp);

    updateclick();
	framecnt++;
}
