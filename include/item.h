#ifndef _ITEM_H
#define _ITEM_H

#include "rectangle.h"
#include <stdint.h>
#include <stddef.h>

typedef struct item {
	const uint8_t *image;
	Rectangle dim;
	
	// 16x16 used for icon
	const uint8_t *imagetb;
	
	uint16_t colors;
	// TODO this may not be necessary
	uint16_t hover_colors;
	
	const char *name;
} Item;

extern Item *helditem;

void drawitem(Item *item);

void drawhelditem();

#endif
