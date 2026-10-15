#ifndef _LABEL_H
#define _LABEL_H

#include <stdint.h>
#include "rectangle.h"
#include "toolbar.h"

#define CHAR_W 8
#define CHAR_H 8
#define LABELPADDING 2

Rect16 getlabeldim(int16_t x, int16_t y, const char *str);
void drawlabeltb(Toolbar *tb, int16_t off, int16_t px, int16_t py, const char *str);
void drawlabelctr(int16_t x, int16_t y, int16_t px, int16_t py, const char *str);

#endif
