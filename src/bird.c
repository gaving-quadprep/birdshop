#include "wasm4.h"
#include "bird.h"
#include "item.h"
#include <stddef.h>

static void _drawitemat(Item *item, void *data);

void drawbird(Bird *bird) {
	foreachpart(bird, bird, &_drawitemat);
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
