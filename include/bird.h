#ifndef _BIRD_H
#define _BIRD_H

#include <stdint.h>
#include <stdbool.h>
#include "rectangle.h"
#include "item.h"

typedef struct fastener {
	int16_t x;
	int16_t y;
	Item *item;
	Item *connected;
	bool isattached;
} Fastener;

typedef struct bird {
	int16_t x;
	int16_t y;
	struct {
		Item *body;
		Item *eye;
		Item *feet;
		Item *head;
		Item *tail;
		Item *wing;
	} parts;
	
	Item **otherparts;
	size_t otherpartcount;

	Fastener *glue;
	size_t gluecount;
	
	Fastener *screws;
	size_t screwcount;
	
	
} Bird;

void drawbird(Bird *bird);
void _do(Item *item, void *data);
void foreachpart(Bird *bird, void *otherdata, void (*fn)(Item*, void*));

#endif
