#include "wasm4.h"
#include "rectangle.h"
#include <stdbool.h>

// wasm4 doesn't provide a way to see if a mouse was clicked,
// so we check if it was held down on  this frame and not the one before

static bool prevleft = false, prevmiddle = false, prevright = false;

// should be called AFTER logic that uses the mouse click function
// so that it revers to the previous and not most recent value
void updateclick() {
	prevleft = *MOUSE_BUTTONS & MOUSE_LEFT;
	prevmiddle = *MOUSE_BUTTONS & MOUSE_MIDDLE;
	prevright = *MOUSE_BUTTONS & MOUSE_RIGHT;
}

bool isleftclick() {
	return (*MOUSE_BUTTONS & MOUSE_LEFT) && !prevleft;
}
bool ismiddleclick() {
	return (*MOUSE_BUTTONS & MOUSE_MIDDLE) && !prevmiddle;
}
bool isrightclick() {
	return (*MOUSE_BUTTONS & MOUSE_RIGHT) && !prevright;
}

bool ismousewithin(Rect16 area) {
	return *MOUSE_X > area.x && *MOUSE_X < area.x + area.width
		&& *MOUSE_Y > area.y && *MOUSE_Y < area.y + area.height;
}
