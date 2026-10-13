#ifndef _ITEM_H
#define _ITEM_H

#include <stdint.h>
#include <stddef.h>

#define ITEM_WIDTH 16
#define ITEM_HEIGHT 16

typedef struct item {
	const uint8_t *image;
	uint16_t colors;
	uint16_t hover_colors;
	const char *name;
} Item;

#endif
