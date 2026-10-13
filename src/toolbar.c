#include "wasm4.h"
#include "toolbar.h"
#include "click.h"
#include "direction.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

void drawtoolbar(Toolbar *tb) {
	uint8_t tbwidth, tbheight, xpos, ypos;
	if (ISVERTICAL(tb->side)) {
		tbwidth = (tb->xpadding * 2)
		+ (uint8_t) (tb->itemcount * tb->imagew)
		// for every n items, there are n-1 spaces between the item
		+ (uint8_t) ((tb->itemcount - 1) * tb->itempadding);

		tbheight = (tb->ypadding * 2) + tb->imageh;

		xpos = (160 - tbwidth) / 2;
		ypos = tb->side == UP ? 0 : (160 - tbheight);
	} else {
		tbwidth = (tb->xpadding * 2) + tb->imageh;

		tbheight = (tb->ypadding * 2)
		+ (uint8_t) (tb->itemcount * tb->imageh)
		+ (uint8_t) ((tb->itemcount - 1) * tb->itempadding);

		xpos = tb->side == LEFT ? 0 : (160 - tbwidth);
		ypos = (160 - tbheight) / 2;
	}

	*DRAW_COLORS = tb->colors;

	rect(xpos, ypos, tbwidth, tbheight);

	uint8_t imagexpos = xpos + tb->xpadding;
	uint8_t imageypos = ypos + tb->ypadding;

	for (size_t i = 0; i < tb->itemcount; i++) {
		Item *item = tb->items[i];
		if (item != NULL) {
			*DRAW_COLORS = item->colors;
			if (*MOUSE_X > imagexpos && *MOUSE_X < imagexpos + tb->imagew
					&& *MOUSE_Y > imageypos && *MOUSE_Y < imageypos + tb->imageh) {
				if (!(*MOUSE_BUTTONS & MOUSE_LEFT))
					*DRAW_COLORS = item->hover_colors;
				if (isleftclick()) {
					if (tb->onclicked != NULL)
						(*tb->onclicked)(tb, i);
				}
			}
			if (item->image != NULL)
				blit(item->image, imagexpos, imageypos, tb->imagew, tb->imageh, BLIT_2BPP);
		}
		if (ISVERTICAL(tb->side))
			imagexpos += tb->imagew + tb->itempadding;
		else
			imageypos += tb->imageh + tb->itempadding;
	}
}

// removes all empty elements
void flatten(Toolbar *tb) {
	bool cont = true;
	for (size_t i = 0; i < tb->itemcount; i++) {
		if (tb->items[i] == NULL) {
			size_t tomove = (tb->itemcount - 1) - i;
			memmove(&tb->items[i], &tb->items[i + 1], tomove * sizeof(Item*));
			tb->itemcount--;
		}
	}
}

void insert(Toolbar *tb, Item *item, size_t position) {
	if (tb->itemcount == tb->maxitems)
		return;
	if (position > tb->maxitems)
		return;
	if (position > tb->itemcount)
		position = tb->itemcount;
	size_t tomove = tb->itemcount - position;
	memmove(&tb->items[position + 1], &tb->items[position], tomove * sizeof(Item*));
	tb->items[position] = item;
	tb->itemcount++;
}
