#include "wasm4.h"
#include "rectangle.h"
#include <stdint.h>
#include <stdbool.h>

// wasm4 doesn't provide a way to see if a mouse was clicked,
// so we check if it was held down on  this frame and not the one before

static uint8_t prevmouse;

// should be called AFTER logic that uses the mouse click function
// so that it revers to the previous and not most recent value
void updateclick() {
	prevmouse = *MOUSE_BUTTONS;
}

bool isleftclick() {
	return (*MOUSE_BUTTONS & ~prevmouse) & MOUSE_LEFT;
}
bool ismiddleclick() {
	return (*MOUSE_BUTTONS & ~prevmouse) & MOUSE_MIDDLE;
}
bool isrightclick() {
	return (*MOUSE_BUTTONS & ~prevmouse) & MOUSE_RIGHT;
}

bool ismousewithin(Rect16 area) {
	return *MOUSE_X > area.x && *MOUSE_X < area.x + area.width
		&& *MOUSE_Y > area.y && *MOUSE_Y < area.y + area.height;
}
