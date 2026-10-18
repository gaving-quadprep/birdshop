#include <stdlib.h>
#include <stdint.h>

#include "pigeon.h"

#include "pigeonbody.h"
#include "pigeonfeet.h"
#include "pigeontail.h"
#include "pigeonwing.h"
#include "pigeonhead.h"
#include "pigeoneye.h"

Bird *mkpigeon() {
	Bird *ret = malloc(sizeof(Bird));

	ret->parts.body = malloc(sizeof(Item));
	*ret->parts.body = (Item) {
		.image = pigeonbody,
		.dim = (Rect16) {
			.x = 5,
			.y = 8,
			.width = 16,
			.height = 16
		},
		.imagetb = pigeonbody,
		.colors = 0x4320,
		.hover_colors = 0x4432,
		.name = "Pigeon Body",
	};

	ret->parts.feet = malloc(sizeof(Item));
	*ret->parts.feet = (Item) {
		.image = pigeonfeet,
		.dim = (Rect16) {
			.x = 8,
			.y = 23,
			.width = 8,
			.height = 5
		},
		.imagetb = NULL,
		.colors = 0x0330,
		.hover_colors = 0x2442,
		.name = "Pigeon Feet",
	};

	ret->parts.wing = malloc(sizeof(Item));
	*ret->parts.wing = (Item) {
		.image = pigeonwing,
		.dim = (Rect16) {
			.x = 5,
			.y = 13,
			.width = 9,
			.height = 6
		},
		.imagetb = NULL,
		.colors = 0x4320,
		.hover_colors = 0x4432,
		.name = "Pigeon Wing",
	};

	ret->parts.tail = malloc(sizeof(Item));
	*ret->parts.tail = (Item) {
		.image = pigeontail,
		.dim = (Rect16) {
			.x = 0,
			.y = 14,
			.width = 7,
			.height = 9
		},
		.imagetb = NULL,
		.colors = 0x4320,
		.hover_colors = 0x4432,
		.name = "Pigeon Tail",
	};

	ret->parts.head = malloc(sizeof(Item));
	*ret->parts.head = (Item) {
		.image = pigeonhead,
		.dim = (Rect16) {
			.x = 13,
			.y = 0,
			.width = 10,
			.height = 13
		},
		.imagetb = NULL, // TODO what should i do here
		.colors = 0x4430,
		.hover_colors = 0x4442,
		.name = "Pigeon Head",
	};

	ret->parts.eye = malloc(sizeof(Item));
	*ret->parts.eye = (Item) {
		.image = pigeoneye,
		.dim = (Rect16) {
			.x = 16,
			.y = 1,
			.width = 3,
			.height = 3
		},
		.imagetb = NULL,
		.colors = 0x4401,
		.hover_colors = 0x4422,
		.name = "Pigeon Eye",
	};
	
	return ret;
}
