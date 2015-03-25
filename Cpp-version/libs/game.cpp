#include "game.hpp"

	game::game(int npcs){
		current = map(); 
        
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
		
		mon_list = new Monster[npcs]();
		num_npcs = npcs;
		for(int i = 0; i < num_npcs; i++){
			while(mon_list[i].pos[0] == 0 || mon_list[i].pos[1] == 0){
				int x = (rand()%158) + 1;
				int y = (rand()%94) + 1;
				if(current.layout[y][x].type == tile_type_floor){
					mon_list[i].pos[0] = x;
					mon_list[i].pos[1] = y;
					current.layout[y][x].mon = &mon_list[i];
				}
			}
			mon_list[i].speed = 5 + (rand()%16);
			mon_list[i].attribs = 0;
			mon_list[i].path_to_player = NULL;
			mon_list[i].last_pc_pos[0] = 255;
			mon_list[i].last_pc_pos[1] = 255;
			mon_list[i].alive = 255;
			
			mon_list[i].attribs = (rand() % 4);
			if(mon_list[i].attribs = 0) mon_list[i].Sprite = '0';
			else if(mon_list[i].attribs = 1) mon_list[i].Sprite = '1';
			else if(mon_list[i].attribs = 2) mon_list[i].Sprite = '2';
			else mon_list[i].Sprite = '3';
		}
	}
	
	game::~game(){
		delete me;
		delete mon_list;
		//delete &current;
	}

	void game::save_game(){
		
	}
	
	void game::load_game(){
		
	}
	
	void game::change_floor(){
		
	}
	
	void game::turn_system(){
		
	}
