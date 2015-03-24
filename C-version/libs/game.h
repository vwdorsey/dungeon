#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "queue.h"
#include "defs.h"

Monster* generate_monster();
Player* generate_PC();

void move_character(void* ch, char type, int d_y, int d_x, t_tile *map);
int* monster_movement(Monster* mon, t_tile* map);
void kill_all_monsters(queue* q);

#endif
