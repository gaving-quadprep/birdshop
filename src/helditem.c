#include "helditem.h"
#include "wasm4.h"

Item *helditem = NULL;

void drawhelditem() {
	if (helditem == NULL)
		return;
	if (helditem->image == NULL)
		return;
	*DRAW_COLORS = helditem->colors;
	blit(helditem->image, *MOUSE_X - ITEM_WIDTH / 2, *MOUSE_Y - ITEM_HEIGHT / 2,
		 ITEM_WIDTH, ITEM_HEIGHT, BLIT_2BPP);
}
