#ifndef _TOOLBAR_H
#define _TOOLBAR_H

#include <stdint.h>
#include <stddef.h>
#include "item.h"
#include "direction.h"
#include "rectangle.h"

typedef struct toolbar {
	Direction side;

	uint8_t xpadding;
	uint8_t ypadding;
	uint8_t itempadding;

	uint8_t imagew;
	uint8_t imageh;

	size_t itemcount;
	size_t maxitems; // it should be able to hold this many items in its buffer
	void (*onclicked)(struct toolbar*, size_t);
	uint16_t colors;
	struct item *items[];
} Toolbar;

Rect16 getsize(Toolbar *tb);
void drawtoolbar(Toolbar *tb);
void flatten(Toolbar *tb);
void insert(Toolbar *tb, Item *item, size_t position);
Item *takeitem(Toolbar *tb, size_t position);
void addspacer(Toolbar *tb);
void handleclick(struct toolbar *tb, size_t item);

#endif
