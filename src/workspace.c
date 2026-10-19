#include "workspace.h"
#include "wasm4.h"
#include "item.h"
#include "bird.h"
#include "7segment.h"
#include "mouse.h"

Workspace *wksp;

void drawworkspace(Workspace *ws) {
	*DRAW_COLORS = 2;
	text(wksp->message, 10, 10);
	drawclock();
	drawbird(ws->bird);
	for (size_t i = 0; i < ws->items->count; i++) {
		Item *item = ws->items->items[i];
		drawitem(item);
		if (helditem == NULL && isleftclick()) {
			if (ismousewithin(item->dim)) {
				helditem = item;
				removeitemfromlist(ws->items, item);
				updateclick(); // do this to avoid immediately placing it
			}
		}
	}
	drawtoolbar(ws->tb);
	addspacer(ws->tb);
	drawhelditem();
}
