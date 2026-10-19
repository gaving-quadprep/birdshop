#include "wasm4.h"
#include "bird.h"
#include "mouse.h"
#include "framecnt.h"

#include <stddef.h>
#include <stdbool.h>

static void _drawitemat(Item *item, void *data);
static void _ismouseinbird(Item *item, void *data);

typedef struct {
	Bird *bird;
	bool *ret;
} _ismouseinbird_params;

void drawbird(Bird *bird) {
	foreachpart(bird, bird, &_drawitemat);
	for (size_t i = 0; i < bird->gluecount; i++) {
		*DRAW_COLORS = 0x0033;
		Fastener f = bird->glue[i];
		if (f.isattached)
			rect(f.x + bird->x, f.y + bird->y, 1, 1);
	}
	if (helditem != NULL && helditem->id == 1) {
		for (size_t i = 0; i < bird->screwcount; i++) {
			*DRAW_COLORS = 0x0011 * ((framecnt / 8) % 4);
			Fastener f = bird->screws[i];
			if (f.isattached)
				rect(f.x + bird->x, f.y + bird->y, 1, 1);
		}
	}
}

// if a function only takes an item as a parameter, this allows you to call it from foreachpart
void _do(Item *item, void *data) {
	((void (*)(Item*))data)(item);
}

static void _drawitemat(Item *item, void *data) {
	Bird *bird = (Bird*)data;
	if (item != NULL)
		drawitemat(item, bird->x, bird->y);
}

void foreachpart(Bird *bird, void *otherdata, void (*fn)(Item*, void*)) {
	fn(bird->parts.body, otherdata);
	fn(bird->parts.feet, otherdata);
	fn(bird->parts.tail, otherdata);
	fn(bird->parts.wing, otherdata);
	fn(bird->parts.head, otherdata);
	fn(bird->parts.eye, otherdata);
	
	if (bird->otherparts  != NULL && bird->otherpartcount > 0) {
		for (size_t i = 0; i < bird->otherpartcount; i++) {
			fn(bird->otherparts[i], otherdata);
		}
	}
}

bool ismouseinbird(Bird *bird) {
	bool ret = false;
	_ismouseinbird_params params = (_ismouseinbird_params) {
		.bird = bird,
		.ret = &ret
	};
	foreachpart(bird, &params, &_ismouseinbird);
	return ret;
}

// this is kinda messy but it

void _ismouseinbird(Item *item, void *data) {
	_ismouseinbird_params *params = (_ismouseinbird_params*)data;
	if(!*(params->ret)) {
		Rect16 rect = item->dim;
		rect.x += params->bird->x;
		rect.y += params->bird->y;
		*(params->ret) = ismousewithin(item->dim);
	}
}
