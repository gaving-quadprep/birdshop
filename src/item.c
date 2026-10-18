#include "item.h"
#include "wasm4.h"
#include "mouse.h"

#include <stdlib.h>
#include <string.h>

Item *helditem = NULL;

typedef struct itemlist {
	size_t count;
	size_t size;
	// this can't be a FAM because it means reallocating the entire list when growing it
	Item **items;
} Itemlist;

// this is a list of items in the workspace not attached to anything
Itemlist *wsitems = NULL;

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

	if (isleftclick()) {

	}
}
