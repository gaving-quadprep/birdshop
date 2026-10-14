#ifndef _MOUSE_H
#define _MOUSE_H

#include "rectangle.h"
#include <stdbool.h>

void updateclick();

bool isleftclick();
bool ismiddleclick();
bool isrightclick();

bool ismousewithin(Rect16 area);

#endif
