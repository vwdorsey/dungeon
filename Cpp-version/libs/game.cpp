#include "game.hpp"

	game::game(){
		current = map(); //Do I have to overload an operator for this?
		
		me = new Player();
		me->Sprite=pc_sprite;
		me->speed=pc_speed;
		while(me->pos[0] == 0 || me->pos[1] == 0){
			int x = (rand()%158) + 1;
			int y = (rand()%94) + 1;
			if(current.layout[y][x].type == tile_type_floor){
				me->pos[0] = x;
				me->pos[1] = y;
				current.layout[y][x].pc = me;
			}
		}
	}
	
	game::~game(){
		delete &current;
	}

	void game::save_game(){
		
	}
	
	void game::load_game(){
		
	}
	
	void game::change_floor(){
		
	}
	
	void game::turn_system(){
		
	}
