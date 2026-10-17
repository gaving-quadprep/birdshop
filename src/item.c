#include "item.h"
#include "wasm4.h"

Item *helditem = NULL;

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
}
