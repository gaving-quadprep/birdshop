#include "item.h"
#include "wasm4.h"
#include "mouse.h"
#include "workspace.h"
#include "toolbar.h"

#include <stdlib.h>
#include <string.h>

Item *helditem = NULL;

void mvitems(Item **items, size_t src, size_t dst, size_t cnt) {
	memmove(&items[dst], &items[src], cnt * sizeof(Item*));
}

void resizeitemlist(Itemlist *list, size_t nextsize) {
	Item **newitems = malloc((sizeof(Item*) * nextsize));
	if (nextsize < list->count)
		list->count = nextsize;
	list->size = nextsize;

	memcpy(newitems, list->items, list->count * sizeof(Item*));

	free(list->items);

	list->items = newitems;

}

Itemlist *mkitemlist(size_t initsize) {
	Itemlist *ret = malloc(sizeof(Itemlist));
	ret->items = malloc(sizeof(Item*) * initsize);
	ret->count = 0;
	ret->size = initsize;
	return ret;
}

void additemtolist(Itemlist *list, Item *item) {
	if (list == NULL || item == NULL)
		return;
	if (list->count == list->size) {
		resizeitemlist(list, list->size * 2);
	}
	list->items[list->count++] = item;
}

void removeitemfromlist(Itemlist *list, Item *item) {
	if (list == NULL || item == NULL)
		return;
	int pos = -1;
	for (size_t i = 0; i < list->count; i++) {
		if (list->items[i] == item) {
			pos = i;
			break;
		}
	}
	if (pos != -1) {
		mvitems(list->items, pos + 1, pos, (list->count - 1) - pos);
		list->count--;
	}
}

void drawitem(Item *item) {
	drawitemat(item, 0, 0);
}

void drawitemat(Item *item, int16_t x, int16_t y) {
	if (item == NULL)
		return;
	if (item->image == NULL)
		return;
	*DRAW_COLORS = item->colors;
	blit(item->image, item->dim.x + x, item->dim.y + y,
		 item->dim.width, item->dim.height, BLIT_2BPP);
}


void drawhelditem() {
	if (helditem == NULL)
		return;
	
	// center on mouse
	helditem->dim.x = *MOUSE_X - (helditem->dim.width / 2);
	helditem->dim.y = *MOUSE_Y - (helditem->dim.height / 2);
	
	drawitem(helditem);

	if (*MOUSE_BUTTONS & MOUSE_LEFT) {
		if (helditem != NULL && helditem->id == 2) {
			Bird *bird = wksp->bird;
			if (bird != NULL && bird->parts.head != NULL) {
				int remaining_attached = 0;
				for (size_t i = 0; i < bird->gluecount; i++) {
					int16_t gx = bird->glue[i].x + bird->x;
					int16_t gy = bird->glue[i].y + bird->y;

					// you can tell im rushing
					if (gx > helditem->dim.x && gy > helditem->dim.y
						&& gx < helditem->dim.x + helditem->dim.width
						&& gy < helditem->dim.y + helditem->dim.height) {
						bird->glue[i].isattached = false;
					}
					remaining_attached += bird->glue[i].isattached? 1: 0;
				}
				if (remaining_attached == 0) {
					// this just assumed its head temporarily
					Item *head = bird->parts.head;
					additemtolist(wksp->items, head);
					head->dim.x += bird->x;
					head->dim.y += bird->y;
					bird->parts.head = NULL;
					wksp->prog++;
					strcpy("Take off the wing", wksp->message);
				}
			}
		}
	}
	// placing items is temporarily disabled due to time constraints
	/*
	if (isleftclick() && !ismousewithin(getsize(wksp->tb))) {
		additemtolist(wksp->items, helditem);
		helditem = NULL;
	}
	*/
}
