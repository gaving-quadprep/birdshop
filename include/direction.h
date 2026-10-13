#ifndef _DIRECTION_H
#define _DIRECTION_H

typedef enum direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
} Direction;

#define DIRTOX(dir) ((dir) == LEFT ? -1 : ((dir) == RIGHT ? 1 : 0))
#define DIRTOY(dir) ((dir) == UP ? -1 : ((dir) == DOWN ? 1 : 0))
#define ISVERTICAL(dir) (((dir) == UP) || ((dir) == DOWN))

#endif
