#include "game.hpp"

	game::game(int npcs){
		current = map();
		mon_turns=0;
		turn=0;
		
		random.seed(rand());
		rand_mon_move = std::uniform_int_distribution<int>(-1, 1);
        
		me = new Player();
		me->Sprite=pc_sprite;
		me->speed=pc_speed;
		me->alive=1;
		me->priority=pc_speed;
		while(me->pos[0] == 0 && me->pos[1] == 0){
			int x = (rand()%(rows-2)) + 1;
			int y = (rand()%(columns-2)) + 1;
			if(current.layout[y][x].type == tile_type_floor){
				me->pos[0] = y;
				me->pos[1] = x; 
				current.layout[y][x].pc = me;
			}
		}
		
		num_npcs = npcs;
		
		for(int i = 0; i <= num_npcs; i++){
			Monster* mon = new Monster();
			while(mon->pos[0] == 0 && mon->pos[1] == 0){
				int x = (rand()%(rows-2)) + 1;
				int y = (rand()%(columns-2)) + 1;
				if(current.layout[y][x].type == tile_type_floor){
					mon->pos[0] = y;
					mon->pos[1] = x;
					current.layout[y][x].mon = mon;
				}
			}
			mon->speed = pc_speed + (rand()%16);
			mon->attribs = 0;
			mon->path_to_player = NULL;
			mon->last_pc_pos[0] = 255;
			mon->last_pc_pos[1] = 255;
			mon->alive = 1;
			
			int intelligence = rand()%2;
			int telepathic = rand()%2;
			
			if(intelligence) mon->attribs += IS_SMART;
			if(telepathic) mon->attribs += TELEPATHIC;
			
			if(mon->attribs == 0) mon->Sprite = '0';
			else if(mon->attribs == 1) mon->Sprite = '1';
			else if(mon->attribs == 2) mon->Sprite = '2';
			else mon->Sprite = '3';
			
			turn_queue.push(mon, mon->speed + pc_speed);
		}
		
		int upstair_y = 0;
		int upstair_x = 0;
		int downstair_y = 0;
		int downstair_x = 0;
		
		while(upstair_y == 0 && upstair_x == 0){
			int x = (rand()%(rows-2)) + 1;
			int y = (rand()%(columns-2)) + 1;
			if(current.layout[y][x].type == tile_type_floor && current.layout[y][x].mon == NULL && current.layout[y][x].pc == NULL){
				upstair_y = y;
				upstair_x = x; 
				current.layout[y][x].type = tile_type_upstair;
			}
		}
		
		while(downstair_y == 0 && downstair_x == 0){
			int x = (rand()%(rows-2)) + 1;
			int y = (rand()%(columns-2)) + 1;
			if(current.layout[y][x].type == tile_type_floor && current.layout[y][x].mon == NULL && current.layout[y][x].pc == NULL){
				downstair_y = y;
				downstair_x = x; 
				current.layout[y][x].type = tile_type_downstair;
			}
		}
	}
	
	game::~game(){
		delete me;
		//delete &current;
	}

	void game::save_game(){
		
	}
	
	void game::load_game(){
		
	}
	
	void game::change_floor(){
		delete mon_list;
		
		current = map();
		
		me->priority = me->speed;
		me->pos[0] = 0;
		me->pos[1] = 0;
		while(me->pos[0] == 0 && me->pos[1] == 0){
			int x = (rand()%(rows-2)) + 1;
			int y = (rand()%(columns-2)) + 1;
			if(current.layout[y][x].type == tile_type_floor){
				me->pos[0] = y;
				me->pos[1] = x; 
				current.layout[y][x].pc = me;
			}
		}
		
		for(int i = 0; i <= num_npcs; i++){
			Monster* mon = new Monster();
			while(mon->pos[0] == 0 && mon->pos[1] == 0){
				int x = (rand()%(rows-2)) + 1;
				int y = (rand()%(columns-2)) + 1;
				if(current.layout[y][x].type == tile_type_floor){
					mon->pos[0] = y;
					mon->pos[1] = x;
					current.layout[y][x].mon = mon;
				}
			}
			mon->speed = 5 + (rand()%16);
			mon->attribs = 0;
			mon->path_to_player = NULL;
			mon->last_pc_pos[0] = 255;
			mon->last_pc_pos[1] = 255;
			mon->alive = 255;
			
			int intelligence = rand()%2;
			int telepathic = rand()%2;
			
			if(intelligence) mon->attribs += IS_SMART;
			if(telepathic) mon->attribs += TELEPATHIC;
			
			if(mon->attribs == 0) mon->Sprite = '0';
			else if(mon->attribs == 1) mon->Sprite = '1';
			else if(mon->attribs == 2) mon->Sprite = '2';
			else mon->Sprite = '3';
			
			turn_queue.push(mon, mon->speed + pc_speed);
		}
		
		int upstair_y = 0;
		int upstair_x = 0;
		int downstair_y = 0;
		int downstair_x = 0;
		
		while(upstair_y == 0 && upstair_x == 0){
			int x = (rand()%(rows-2)) + 1;
			int y = (rand()%(columns-2)) + 1;
			if(current.layout[y][x].type == tile_type_floor && current.layout[y][x].mon == NULL && current.layout[y][x].pc == NULL){
				upstair_y = y;
				upstair_x = x; 
				current.layout[y][x].type = tile_type_upstair;
			}
		}
		
		while(downstair_y == 0 && downstair_x == 0){
			int x = (rand()%(rows-2)) + 1;
			int y = (rand()%(columns-2)) + 1;
			if(current.layout[y][x].type == tile_type_floor && current.layout[y][x].mon == NULL && current.layout[y][x].pc == NULL){
				downstair_y = y;
				downstair_x = x; 
				current.layout[y][x].type = tile_type_downstair;
			}
		}
	}
	
	int game::turn_system(){
		if(turn_queue.get_size() == 0) return -1;
		int next_priority = turn_queue.lowest_priority();
		Monster* mon = (Monster*) turn_queue.pull();
		if(next_priority < me->priority){
			if(mon->alive == 0) delete mon;
			else{
				determine_mon_next_move(mon);
				turn_queue.push(mon, next_priority + mon->speed);
			}
			return 1;
		}
		else {
			turn_queue.push(mon, next_priority);
			return 0;
		}
	}

	void game::move_player(int d_y, int d_x){
		Player* c = me;
		tile next_tile = current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x];
		if(next_tile.type == tile_type_floor || next_tile.type == tile_type_downstair || next_tile.type == tile_type_upstair){
			if(next_tile.mon){
				Monster* killed_mon = next_tile.mon;
				killed_mon -> alive = 0;
			}
			
			current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].pc = c;
			if(d_x != 0 || d_y != 0) current.layout[(c->pos[0])][(c->pos[1])].pc = NULL;
			c->pos[0] = (c->pos[0])+d_y;
			c->pos[1] = (c->pos[1])+d_x;
		}
	}

	void game::determine_mon_next_move(Monster *mon){
		int y = rand_mon_move(random);
		int x = rand_mon_move(random);
		dijkstra path_maker = dijkstra();
		
		mon_turns++;
		if(me->alive){
		if(x == 2) x = -1;
		if(y == 2) y = -1;
		
		if(mon -> attribs == IS_SMART + TELEPATHIC){ 
			if(mon->last_pc_pos[0] != me->pos[0] || mon->last_pc_pos[1] != me->pos[1]){
				mon->path_to_player = path_maker.Dijkstra(current.layout, mon->pos[0], mon->pos[1], me->pos[0], me->pos[1]);
				mon->last_pc_pos[0] = me->pos[0];
				mon->last_pc_pos[1] = me->pos[1];
			}
			point next_move = *((mon -> path_to_player)+1);
			if(next_move.n_x > 159 || next_move.n_y > 95 || mon->path_to_player->path_size==1){
				check_monster_at_player(mon);
			}
			else if(current.layout[next_move.n_y][next_move.n_x].type == tile_type_floor){
				move_monster(mon, next_move.n_y-mon->pos[0], next_move.n_x-mon->pos[1]);
			}
		}
		else if(mon -> attribs == IS_SMART){
			move_monster(mon, y, x);
		}
		else if(mon -> attribs == TELEPATHIC){
			move_monster(mon, y, x);
		}
		else{
			move_monster(mon, y, x);
		}
	}
}
	
	void game::move_monster(Monster *c, int d_y, int d_x){
		if(current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].type == tile_type_floor){
			if(current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].mon && current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].mon != c){
				Monster* killed_mon = current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].mon;
				killed_mon -> alive = 0;
			}
			
			if(current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].pc){
				Player* pc = current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].pc;
				pc -> alive = 0;
			}
			
			current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].mon = c;
			if(d_x != 0 || d_y != 0) current.layout[c->pos[0]][c->pos[1]].mon = NULL;
			c->pos[0] = (c->pos[0])+d_y;
			c->pos[1] = (c->pos[1])+d_x;
		}
	}
	
	void game::check_monster_at_player(Monster *mon){
		int x = mon -> pos[1];
		int y = mon -> pos[0];
		
		if(current.layout[y][x+1].pc) current.layout[y][x+1].pc -> alive = 0;
		if(current.layout[y][x-1].pc) current.layout[y][x-1].pc -> alive = 0;
		if(current.layout[y+1][x].pc) current.layout[y+1][x].pc -> alive = 0;
		if(current.layout[y-1][x].pc) current.layout[y-1][x].pc -> alive = 0;
		if(current.layout[y+1][x+1].pc) current.layout[y+1][x+1].pc -> alive = 0;
		if(current.layout[y+1][x-1].pc) current.layout[y+1][x-1].pc -> alive = 0;
		if(current.layout[y-1][x+1].pc) current.layout[y-1][x+1].pc -> alive = 0;
		if(current.layout[y-1][x-1].pc) current.layout[y-1][x-1].pc -> alive = 0;
	}
	
	int game::user_move(){
		me->priority += pc_speed;
		turn++;
		
		int status_flag = 1;
		char sys_input = 0;
		
		sys_input = getchar();
		status_flag = interpret_input(sys_input);
		
		if(status_flag == 0){
			save_game();
			return 0;
		}
		else if(status_flag == 2){
			move_player(-1,0);
			return 1;
		}
		else if(status_flag == 3){
			move_player(1,0);
			return 1;
		}
		else if(status_flag == 4){
			move_player(0,-1);
			return 1;
		}
		else if(status_flag == 5){
			move_player(0,1);
			return 1;
		}
		else if(status_flag == 6){
			move_player(-1,-1);
			return 1;
		}
		else if(status_flag == 7){
			move_player(1,-1);
			return 1;
		}
		else if(status_flag == 8){
			move_player(-1,1);
			return 1;
		}
		else if(status_flag == 9){
			move_player(1,1);
			return 1;
		}
		else if(status_flag == 10){
			change_floor();
			return 1;
		}
		else if(status_flag == 11){
			return 1;
		}
		else if(status_flag == 12){
			mode = 1;
			return 1;
		}
		else if(status_flag == 13){
			mode = 0;
			return 1;
		}
		else return 1;
	}
	
	int game::interpret_input(char input){
		if(input == save_and_exit) return 0;
		else if(input == num_pad_up || input == kb_up) return 2;
		else if(input == num_pad_down || input == kb_down) return 3;
		else if(input == num_pad_left || input == kb_left) return 4;
		else if(input == num_pad_right || input == kb_right) return 5;
		else if(input == num_pad_lfup || input == kb_lfup) return 6;
		else if(input == num_pad_lfdn || input == kb_lfdn) return 7;
		else if(input == num_pad_rgup || input == kb_rgup) return 8;
		else if(input == num_pad_rgdn || input == kb_rgdn) return 9;
		else if(input == go_upstairs || input == go_downstairs) return 10;
		else if(input == rest) return 11;
		else if(input == to_look_mode) return 12;
		else if(input == to_control_mode) return 13;
		else return 1;
	}
	
