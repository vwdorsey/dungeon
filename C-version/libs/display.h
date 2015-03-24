#ifndef DISPLAY_H
#define DISPLAY_H

#include "queue.h"
#include "defs.h"

void end_session();
void init_display();
void redraw(t_tile map[96][160], Player* me);

#endif
