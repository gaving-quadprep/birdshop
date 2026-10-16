#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include <stdint.h>

typedef struct rectangle {
	int x;
	int y;
	unsigned int width;
	unsigned int height;
} Rectangle;

typedef struct rect16 {
	int16_t x;
	int16_t y;
	uint16_t width;
	uint16_t height;
} Rect16;

#endif
