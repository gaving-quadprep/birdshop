#ifndef _WORKSPACE_H
#define _WORKSPACE_H

#include "item.h"
#include "bird.h"
#include "toolbar.h"

typedef struct workspace {
	Toolbar *tb;
	Bird *bird;
	Itemlist *items;
	bool hasclock;
	char *message;
	int prog;
} Workspace;

extern Workspace *wksp;

void drawworkspace(Workspace *ws);

#endif
