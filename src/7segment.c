#include "wasm4.h"
#include <stdint.h>
#include <stdbool.h>

static void drawsegment(int16_t x, int16_t y, uint8_t segment, bool on);

void draw7segment(int16_t x, int16_t y, char digit) {
	uint8_t segments = 0;
	/*
	0=lsb
	 -0-
	|   |
	1   2
	|   |
	 -3-
	|   |
	4   5
	|   |
	 -6- .7
	*/
	switch (digit) {
	case '0':
		segments = 0b01110111;
		break;
	case '1':
		segments = 0b00100100;
		break;
	case '2':
		segments = 0b01011101;
		break;
	case '3':
		segments = 0b01101101;
		break;
	case '4':
		segments = 0b00101110;
		break;
	case '5':
		segments = 0b01101011;
		break;
	case '6':
		segments = 0b01111011;
		break;
	case '7':
		segments = 0b00100101;
		break;
	case '8':
		segments = 0b01111111;
		break;
	case '9':
		segments = 0b01101111;
		break;
	case '.':
		segments = 0b10000000;
		break;
	}
	uint8_t seg = 0;
	while (seg < 8) {
		drawsegment(x, y, seg, segments & 1);
		segments >>= 1;
		seg++;
	}
}

static void drawsegment(int16_t x, int16_t y, uint8_t segment, bool on) {
	segment &= 0b111; // there should only be this many possibilities
	// rect uses color 2 as the outline, and hline uses color 1
	// since it's only 1 pixel these appear the same
	// and it's simpler than a lot of bit manipulation to swap the colors
	switch (segment) {
		case 0:
			on ? rect(x+1, y, 2, 1) : hline(x+1, y, 2);
			break;
		case 1:
			on ? rect(x, y+1, 1, 2) : vline(x, y+1, 2);
			break;
		case 2:
			on ? rect(x+3, y+1, 1, 2) : vline(x+3, y+1, 2);
			break;
		case 3:
			on ? rect(x+1, y+3, 2, 1) : hline(x+1, y+3, 2);
			break;
		case 4:
			on ? rect(x, y+4, 1, 2) : vline(x, y+4, 2);
			break;
		case 5:
			on ? rect(x+3, y+4, 1, 2) : vline(x+3, y+4, 2);
			break;
		case 6:
			on ? rect(x+1, y+6, 2, 1) : hline(x+1, y+6, 2);
			break;
		/*
		case 7:
			on ? rect(x+4, y+7, 1, 1) : hline(x+4, y+7, 1);
			break; */
	}
}