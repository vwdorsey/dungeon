#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "game.h"
#include "tile.h"
#include "defs.h"

Player* generate_PC(){
    
    Player* new_pc = malloc(sizeof(Player));
    
    new_pc->Sprite = '@';
    new_pc->pos[0] = 0;
    new_pc->pos[1] = 0;
    new_pc->speed = 10;
    new_pc->alive = 255;
    
    return new_pc;
    
}

Monster* generate_monster(){
    
    Monster* new_mon = malloc(sizeof(Monster));
    
    new_mon->Sprite = 65 + (rand()%58);
    new_mon->pos[0] = 0;
    new_mon->pos[1] = 0;
    new_mon->speed = 5 + (rand()%16);
    new_mon->attribs = 0;
    new_mon->path_to_player = NULL;
    new_mon->alive = 255;
    
    if(rand() % 2) new_mon->attribs += IS_SMART;
    if(rand() % 2) new_mon->attribs += TELEPATHIC;
    
    if(new_mon->attribs == 3) new_mon->Sprite = '%';
    
    return new_mon;

}

/*
 * Directions: 0-forward, 1-left, 2-backward, 3-right,
 *             4-back-left, 5-back-right, 6-forward-left, 
 *             7-forward-right
 */
void move_character(void* ch, char type, int d_y, int d_x, t_tile *map){
    if(type == 'm'){
        Monster* c = (Monster*) ch;
        if(map[(((c->pos[0])+d_y)*160)+((c->pos[1])+d_x)].type == tile_type_floor){
            if(map[(((c->pos[0])+d_y)*160)+((c->pos[1])+d_x)].mon){
                Monster* killed_mon = map[(((c->pos[0])+d_y)*160)+((c->pos[1])+d_x)].mon;
                killed_mon -> alive = 0;
            }
            
            if(map[(((c->pos[0])+d_y)*160)+((c->pos[1])+d_x)].pc){
                Player* pc = map[(((c->pos[0])+d_y)*160)+((c->pos[1])+d_x)].pc;
                pc -> alive = 0;
            }
            
            //map[c->pos[0]][c->pos[1]].type = '.';
            map[(((c->pos[0])+d_y)*160)+((c->pos[1])+d_x)].mon = c;
            if(d_x != 0 || d_y != 0) map[((c->pos[0])*160)+(c->pos[1])].mon = NULL;
            c->pos[0] = (c->pos[0])+d_y;
            c->pos[1] = (c->pos[1])+d_x;
            //map[c->pos[0]][c->pos[1]].type = c -> Sprite;
        }
	}
    if(type == 'p'){
        Player* c = (Player*) ch;
        if(map[(((c->pos[0])+d_y)*160)+((c->pos[1])+d_x)].type == tile_type_floor){
			if(map[(((c->pos[0])+d_y)*160)+((c->pos[1])+d_x)].mon){
				Monster* killed_mon = map[(((c->pos[0])+d_y)*160)+((c->pos[1])+d_x)].mon;
				killed_mon -> alive = 0;
			}
			
			map[(((c->pos[0])+d_y)*160)+((c->pos[1])+d_x)].pc = c;
			if(d_x != 0 || d_y != 0) map[(((c->pos[0]))*160)+((c->pos[1]))].pc = NULL;
			c->pos[0] = (c->pos[0])+d_y;
			c->pos[1] = (c->pos[1])+d_x;
        }
    }
}

int* monster_movement(Monster* mon, t_tile *map){
	int* delta = malloc(sizeof(int) * 2);
	delta[0] = 0;
    delta[1] = 0;
	if(mon -> attribs == IS_SMART + TELEPATHIC){
		point next_move = *((mon -> path_to_player)+1);
		if(next_move.n_x > 159 || next_move.n_y > 95 || mon->path_to_player->path_size==1){
			int x = mon -> pos[1];
			int y = mon -> pos[0];
			if(map[(y*160)+x+1].pc) map[(y*160)+x+1].pc -> alive = 0;
			if(map[(y*160)+x-1].pc) map[(y*160)+x-1].pc -> alive = 0;
			if(map[((y+1)*160)+x].pc) map[((y+1)*160)+x].pc -> alive = 0;
			if(map[((y-1)*160)+x].pc) map[((y-1)*160)+x].pc -> alive = 0;
			if(map[((y+1)*160)+x+1].pc) map[((y+1)*160)+x+1].pc -> alive = 0;
			if(map[((y+1)*160)+x-1].pc) map[((y+1)*160)+x-1].pc -> alive = 0;
			if(map[((y-1)*160)+x+1].pc) map[((y-1)*160)+x+1].pc -> alive = 0;
			if(map[((y-1)*160)+x-1].pc) map[((y-1)*160)+x-1].pc -> alive = 0;
		}
		else if(map[((next_move.n_y)*160)+(next_move.n_x)].type == tile_type_floor){
            if(map[((next_move.n_y)*160)+(next_move.n_x)].mon){
                Monster* killed_mon = map[((next_move.n_y)*160)+(next_move.n_x)].mon;
                killed_mon -> alive = 0;
            }
            
            if(map[((next_move.n_y)*160)+(next_move.n_x)].pc){
                Player* pc = map[((next_move.n_y)*160)+(next_move.n_x)].pc;
                pc -> alive = 0;
            }
            
            map[((next_move.n_y)*160)+(next_move.n_x)].mon = mon;
            map[((mon->pos[0])*160)+(mon->pos[1])].mon = NULL;
            mon->pos[0] = (next_move.n_y);
            mon->pos[1] = (next_move.n_x);
        }
	}
	else if(mon -> attribs == IS_SMART){
		delta[1] = rand()%3;
		delta[0] = rand()%3;
		
		if(delta[1] == 2) delta[1] = -1;
		if(delta[0] == 2) delta[0] = -1;
	}
	else if(mon -> attribs == TELEPATHIC){
		delta[1] = rand()%3;
		delta[0] = rand()%3;
		
		if(delta[1] == 2) delta[1] = -1;
		if(delta[0] == 2) delta[0] = -1;
	}
	else{
		delta[1] = rand()%3;
		delta[0] = rand()%3;
		
		if(delta[1] == 2) delta[1] = -1;
		if(delta[0] == 2) delta[0] = -1;
	}
	return delta;
}

void kill_all_monsters(queue* q){
    
    while(q -> queue_size != 0){
        void* current = queue_find_lowest(q);
        Monster *m = (Monster*) current;
        if(m -> path_to_player) free(m -> path_to_player);
        free(current);
    }
    
    kill_queue(q);
}
