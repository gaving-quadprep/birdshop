#include "wasm4.h"
#include "toolbar.h"
#include "mouse.h"
#include "direction.h"
#include "helditem.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

Rect16 getsize(Toolbar *tb) {
	uint16_t tbwidth, tbheight;
	int16_t xpos, ypos;
	if (ISVERTICAL(tb->side)) {
		tbwidth = (tb->xpadding * 2)
		+ (uint16_t) (tb->itemcount * tb->imagew)
		// for every n items, there are n-1 spaces between the item
		+ (uint16_t) ((tb->itemcount - 1) * tb->itempadding);

		tbheight = (tb->ypadding * 2) + tb->imageh;

		xpos = (160 - tbwidth) / 2;
		ypos = tb->side == UP ? 0 : (160 - tbheight);
	} else {
		tbwidth = (tb->xpadding * 2) + tb->imageh;

		tbheight = (tb->ypadding * 2)
		+ (uint16_t) (tb->itemcount * tb->imageh)
		+ (uint16_t) ((tb->itemcount - 1) * tb->itempadding);

		xpos = tb->side == LEFT ? 0 : (160 - tbwidth);
		ypos = (160 - tbheight) / 2;
	}
	return (Rect16){
		.x = xpos,
		.y = ypos,
		.width = tbwidth,
		.height = tbheight,
	};
}

void drawtoolbar(Toolbar *tb) {
	Rect16 tbpos = getsize(tb);

	*DRAW_COLORS = tb->colors;

	rect(tbpos.x, tbpos.y, tbpos.width, tbpos.height);

	int16_t imagexpos = tbpos.x + tb->xpadding;
	int16_t imageypos = tbpos.y + tb->ypadding;
	for (size_t i = 0; i < tb->itemcount; i++) {
		Item *item = tb->items[i];
		bool within = ismousewithin((Rect16){imagexpos, imageypos, tb->imagew, tb->imageh});
		if (within && isleftclick())
			if (tb->onclicked != NULL)
				(*tb->onclicked)(tb, i);

		if (item != NULL) {
			*DRAW_COLORS = item->colors;
			if (within) {
				if (!(*MOUSE_BUTTONS & MOUSE_LEFT))
					*DRAW_COLORS = item->hover_colors;
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
			mvitems(tb, i + 1, i, tomove);
			tb->itemcount--;
		}
	}
}

void mvitems(Toolbar *tb, size_t src, size_t dst, size_t cnt) {
	memmove(&tb->items[dst], &tb->items[src], cnt * sizeof(Item*));
}

void insert(Toolbar *tb, Item *item, size_t position) {
	if (tb->itemcount == tb->maxitems)
		return;
	if (position > tb->maxitems)
		return;
	if (position > tb->itemcount)
		position = tb->itemcount;
	size_t tomove = tb->itemcount - position;
	mvitems(tb, position, position + 1, tomove);
	tb->items[position] = item;
	tb->itemcount++;
}

Item *take(Toolbar *tb, size_t position) {
	Item *ret = tb->items[position];
	tb->items[position] = NULL;
	flatten(tb);
	return ret;
}

void checkplace(Toolbar *tb) {
	static int spacerpos = -1;
	Rect16 tbpos = getsize(tb);
	if (helditem != NULL) {
		if (ismousewithin(tbpos)) {
			size_t hoverpos;
			if (ISVERTICAL(tb->side)) {
				hoverpos = (*MOUSE_X - tbpos.x) / (tb->imagew + tb->itempadding);
			} else {
				hoverpos = (*MOUSE_Y - tbpos.y) / (tb->imageh + tb->itempadding);
			}
			if (spacerpos != -1) {
				int tomove = spacerpos - hoverpos;
				if (tomove < 0) {
					mvitems(tb, spacerpos + 1, spacerpos, -tomove);
				} else {
					mvitems(tb, hoverpos, hoverpos + 1, tomove);
				}
				tb->items[hoverpos] = NULL;
			} else {
				insert(tb, NULL, hoverpos);
			}
			spacerpos = hoverpos;
		} else {
			spacerpos = -1;
			flatten(tb);
		}
	} else {
		spacerpos = -1;
	}
}
