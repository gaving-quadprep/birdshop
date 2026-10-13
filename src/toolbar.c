#include "wasm4.h"
#include "toolbar.h"
#include "click.h"
#include <stddef.h>
#include <stdint.h>

void draw_toolbar(struct toolbar *tb) {
	uint8_t tbwidth = (tb->xpadding * 2)
	+ (uint8_t) (tb->itemcount * tb->imagew)
	// for every n items, there are n-1 spaces between the item
	+ (uint8_t) ((tb->itemcount - 1) * tb->itempadding);

	uint8_t tbheight = (tb->ypadding * 2) + tb->imageh;
	// canvas is 160x160
	// first is divided by 2 so it's centered
	uint8_t xpos = (160 - tbwidth) / 2;
	uint8_t ypos = (160 - tbheight);

	*DRAW_COLORS = 0x0021;

	rect(xpos, ypos, tbwidth, tbheight);

	uint8_t imagexpos = xpos + tb->xpadding;
	uint8_t imageypos = ypos + tb->ypadding;

	for (size_t i = 0; i < tb->itemcount; i++) {
		struct tbentry entry = tb->items[i];

		*DRAW_COLORS = entry.colors;
		if (*MOUSE_X > imagexpos && *MOUSE_X < imagexpos + tb->imagew
				&& *MOUSE_Y > imageypos && *MOUSE_Y < imageypos + tb->imageh) {
			if (!(*MOUSE_BUTTONS & MOUSE_LEFT))
				*DRAW_COLORS = entry.hover_colors;
			if (isleftclick()) {
				if (entry.onclicked != NULL)
					(*entry.onclicked)(tb, i);
			}
		}

		if (entry.image != NULL)
			blit(entry.image, imagexpos, imageypos, tb->imagew, tb->imageh, BLIT_2BPP);

		imagexpos += tb->imagew + tb->itempadding;
	}
}
