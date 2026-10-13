#ifndef _TOOLBAR_H
#define _TOOLBAR_H

#include <stdint.h>
#include <stddef.h>

struct tbentry {
	const uint8_t *image;
	uint16_t colors;
	uint16_t hover_colors;
	const char *name;
	void (*onclicked)();
};

struct toolbar {
	uint8_t xpadding;
	uint8_t ypadding;
	uint8_t itempadding;

	uint8_t imagew;
	uint8_t imageh;

	size_t itemcount;
	struct tbentry items[];
};

void draw_toolbar(struct toolbar *tb);

#endif
