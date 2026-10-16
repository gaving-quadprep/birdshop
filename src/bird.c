#include "wasm4.h"
#include "bird.h"
#include "item.h"
#include <stddef.h>

static void moveitem(Item *item, void *data);

void drawbird(Bird *bird) {
	foreachpart(bird, &drawitem, &_do);
}

// if a function only takes an item as a parameter, this allows you to call it from foreachpart
void _do(Item *item, void *data) {
	((void (*)(Item*))data)(item);
}

void foreachpart(Bird *bird, void *otherdata, void (*fn)(Item*, void*)) {
	fn(bird->parts.body, otherdata);
	fn(bird->parts.eye, otherdata);
	fn(bird->parts.feet, otherdata);
	fn(bird->parts.head, otherdata);
	fn(bird->parts.tail, otherdata);
	fn(bird->parts.wing, otherdata);
	
	if (bird->otherparts  != NULL && bird->otherpartcount > 0) {
		for (size_t i=0; i<bird->otherpartcount; i++) {
			fn(bird->otherparts[i], otherdata);
		}
	}
}

void movebird(Bird *bird, int16_t x, int16_t y) {
	int16_t xy[2] = {x, y};
	foreachpart(bird, xy, &moveitem);
}

static void moveitem(Item *item, void *data) {
	int16_t *xy = (int16_t*)data;
	item->dim.x += xy[0];
	item->dim.y += xy[1];
}