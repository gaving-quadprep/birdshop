#ifndef _BIRD_H
#define _BIRD_H

#include <stdint.h>
#include "rectangle.h"
#include "item.h"

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
	
	// each one of these stores an x and y coordinate
	// so getting the nth screw would be screws[n*2]
	// only int8_t because it's relative to the bird which should be that small
	int8_t *glue;
	size_t gluecount;
	
	int8_t *screws;
	size_t screwcount;
	
	
} Bird;

void drawbird(Bird *bird);
void _do(Item *item, void *data);
void foreachpart(Bird *bird, void *otherdata, void (*fn)(Item*, void*));

#endif
