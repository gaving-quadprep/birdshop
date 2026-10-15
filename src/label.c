#include "wasm4.h"
#include "label.h"
#include "toolbar.h"
#include "rectangle.h"
#include "direction.h"
#include <string.h>

static void _drawlabel(Rect16 dim, int16_t px, int16_t py, const char *str);

Rect16 getlabeldim(int16_t x, int16_t y, const char *str) {
	size_t textlen = strlen(str);
	uint16_t w = (textlen * CHAR_W) + 2 * LABELPADDING;
	uint8_t newlines = 1;
	const char *tptr = str;
	while ((tptr = strchr(tptr, '\n')) != NULL) {
		newlines++;
		tptr++;
	}
	uint16_t h = (newlines * CHAR_H) + 2 * LABELPADDING;
	return (Rect16) {
		.x = x,
		.y = y,
		.width = w,
		.height = h,
	};
}

void drawlabeltb(Toolbar *tb, int16_t off, int16_t px, int16_t py, const char *str) {
	Rect16 dim = getlabeldim(0, 0, str);
	switch(tb->side) {
		case UP:
			dim.x = (160 - dim.width) / 2;
			dim.y = ((tb->ypadding * 2) + tb->imageh) + off;
			break;
		case DOWN:
			dim.x = (160 - dim.width) / 2;
			dim.y = 160 - (((tb->ypadding * 2) + tb->imageh) + off + dim.height);
			break;
		case LEFT:
			dim.x = ((tb->xpadding * 2) + tb->imagew) + off;
			dim.y = (160 - dim.height) / 2;
			break;
		case RIGHT:
			dim.x = 160 - (((tb->xpadding * 2) + tb->imagew) + off + dim.width);
			dim.y = (160 - dim.height) / 2;
			break;
	}
	_drawlabel(dim, px, py, str);
}

void drawlabelctr(int16_t x, int16_t y, int16_t px, int16_t py, const char *str) {
	Rect16 dim = getlabeldim(x, y, str);
	dim.x += dim.width / 2;
	dim.y += dim.height / 2;
	_drawlabel(dim, px, py, str);
}

static void _drawlabel(Rect16 dim, int16_t px, int16_t py, const char *str) {
	*DRAW_COLORS = 0x0003;
	line(dim.x + (dim.width / 2), dim.y + (dim.height / 2), px, py);
	*DRAW_COLORS = 0x0021;
	rect(dim.x, dim.y, dim.width, dim.height);
	*DRAW_COLORS = 0x0013;
	text(str, dim.x + LABELPADDING, dim.y + LABELPADDING);
}

