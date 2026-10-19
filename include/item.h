#ifndef _ITEM_H
#define _ITEM_H

#include "rectangle.h"
#include <stdint.h>
#include <stddef.h>

typedef struct item {
	const uint8_t *image;
	Rect16 dim;
	
	// 16x16 used for icon
	const uint8_t *imagetb;
	
	uint16_t colors;
	// TODO this may not be necessary
	uint16_t hover_colors;

	uint8_t id; //hack because im running out of time
	
	const char *name;
} Item;

typedef struct itemlist {
	size_t count;
	size_t size;
	// this can't be a FAM because it means reallocating the entire list when growing it
	Item **items;
} Itemlist;

extern Item *helditem;
extern Itemlist *wsitems;

void mvitems(Item **items, size_t src, size_t dst, size_t cnt);

void resizeitemlist(Itemlist *list, size_t nextsize);
Itemlist *mkitemlist(size_t initsize);
void additemtolist(Itemlist *list, Item *item);
void removeitemfromlist(Itemlist *list, Item *item);

void drawitem(Item *item);
void drawitemat(Item *item, int16_t x, int16_t y);
void drawhelditem();

#endif
