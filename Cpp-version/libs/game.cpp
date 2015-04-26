#include "game.hpp"
#include "parser.hpp"

	/* LEGACY CODE - Old Game Creation System. Needs Renovations.
	game::game(int npcs){
		current = map();
		mon_turns=0;
		turn=0;
		
		random.seed(rand());
		rand_mon_move = std::uniform_int_distribution<int>(-1, 1);
        
		me = new PC();
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

		for(int i = 0; i <= npcs; i++){
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
	*/
	game::game(int npcs, int objs){
		parser parser_system;
		current = map();
		mon_turns=0;
		turn=0;
		
		random.seed(rand());
		rand_mon_move = std::uniform_int_distribution<int>(-1, 1);
		std::vector<Char_template*> char_templates = parser_system.parse_defs_file();
		std::vector<Obj_template*> obj_templates = parser_system.parse_objs_file();
		monsters = npcs;
		objects = objs;
        
		me = new PC();
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

		for(int i = 0; i <= npcs; i++){
			int char_no = rand()%char_templates.size();
			Monster* mon = new Monster(char_templates[char_no]); //MEMORY LEAK - Not being deleted on exit.
			
			while(mon->pos[0] == 0 && mon->pos[1] == 0){
				int x = (rand()%(rows-2)) + 1;
				int y = (rand()%(columns-2)) + 1;
				if(current.layout[y][x].type == tile_type_floor && !(current.layout[y][x].mon)){
					mon->pos[0] = y;
					mon->pos[1] = x;
					current.layout[y][x].mon = mon;
				}
			}
			
			mon->path_to_player = NULL;
			mon->last_pc_pos[0] = 255;
			mon->last_pc_pos[1] = 255;
			mon->alive = 1;

			turn_queue.push(mon, mon->Speed + pc_speed);
		}

		for(int i = 0; i <= objs; i++){
			int obj_no = rand()%obj_templates.size();
			Object* o = new Object(obj_templates[obj_no]);
			int placed = 0;
			while(!placed){
				int x = (rand()%(rows-2)) + 1;
				int y = (rand()%(columns-2)) + 1;
				if(current.layout[y][x].type == tile_type_floor && !(current.layout[y][x].obj)){
					o->pos[0] = y;
					o->pos[1] = x;
					current.layout[y][x].obj = o;
					placed = 1;
				}
			}
			obj_vect.push_back(o);
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
		parser_system.kill_mon_defs(char_templates);
		parser_system.kill_obj_defs(obj_templates); 
	}
	
	game::~game(){
	  	delete me;
		//delete &current;
		while(turn_queue.get_size() > 0){
			Monster* mon = (Monster*) turn_queue.pull();
			delete mon;
		}
		while(obj_vect.size() > 0){
			Object* tmp = obj_vect.back();
			delete tmp;
			obj_vect.pop_back();
		}
		parser parser_system;

	}

	void game::save_game(){
		
	}
	
	void game::load_game(){
		
	}
	
	void game::change_floor(){ 
		delete mon_list;
		while(obj_vect.size() > 0){
			Object* tmp = obj_vect.back();
			delete tmp;
			obj_vect.pop_back();
		}
		parser parser_system;
		current = map();
		std::vector<Char_template*> char_templates = parser_system.parse_defs_file();
		std::vector<Obj_template*> obj_templates = parser_system.parse_objs_file();
		
		me->priority = me->Speed;
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
		
		for(int i = 0; i <= monsters; i++){
			int char_no = rand()%char_templates.size();
			Monster* mon = new Monster(char_templates[char_no]); //MEMORY LEAK - Not being deleted on exit.
			
			while(mon->pos[0] == 0 && mon->pos[1] == 0){
				int x = (rand()%(rows-2)) + 1;
				int y = (rand()%(columns-2)) + 1;
				if(current.layout[y][x].type == tile_type_floor && !(current.layout[y][x].mon)){
					mon->pos[0] = y;
					mon->pos[1] = x;
					current.layout[y][x].mon = mon;
				}
			}
			
			mon->path_to_player = NULL;
			mon->last_pc_pos[0] = 255;
			mon->last_pc_pos[1] = 255;
			mon->alive = 1;

			turn_queue.push(mon, mon->Speed + pc_speed);
		}

		for(int i = 0; i <= objects; i++){
			int obj_no = rand()%obj_templates.size();
			Object* o = new Object(obj_templates[obj_no]);
			int placed = 0;
			while(!placed){
				int x = (rand()%(rows-2)) + 1;
				int y = (rand()%(columns-2)) + 1;
				if(current.layout[y][x].type == tile_type_floor && !(current.layout[y][x].obj)){
					o->pos[0] = y;
					o->pos[1] = x;
					current.layout[y][x].obj = o;
					placed = 1;
				}
			}
			obj_vect.push_back(o);
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
		parser_system.kill_mon_defs(char_templates);
		parser_system.kill_obj_defs(obj_templates); 
	}
	
	int game::turn_system(){
		if(turn_queue.get_size() == 0) return -1;
		int next_priority = turn_queue.lowest_priority();
		Monster* mon = (Monster*) turn_queue.pull();
		if(next_priority < me->priority){
			if(mon->alive == 0) delete mon;
			else{
				determine_mon_next_move(mon);
				turn_queue.push(mon, next_priority + mon->Speed);
			}
			return 1;
		}
		else {
			turn_queue.push(mon, next_priority);
			return 0;
		}
	}

	void game::move_player(int d_y, int d_x){
		PC* c = me;
		tile next_tile = current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x];
		if(next_tile.type == tile_type_floor || next_tile.type == tile_type_downstair || next_tile.type == tile_type_upstair){
			if(next_tile.mon){
				Monster* mon = next_tile.mon;
				//killed_mon -> alive = 0;
				do_battle(mon);
				return;
			}

			current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].pc = c;
			if(d_x != 0 || d_y != 0) current.layout[(c->pos[0])][(c->pos[1])].pc = NULL;
			c->pos[0] = (c->pos[0])+d_y;
			c->pos[1] = (c->pos[1])+d_x;
			if(current.layout[c->pos[0]][c->pos[1]].obj != NULL && me->backpack.size()<10){
				me->backpack.push_back(current.layout[c->pos[0]][c->pos[1]].obj);
				current.layout[c->pos[0]][c->pos[1]].obj = NULL;
			}
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
			/*
			if(mon->last_pc_pos[0] != me->pos[0] || mon->last_pc_pos[1] != me->pos[1]){
				point* p = path_maker.Dijkstra(current.layout, mon->pos[0], mon->pos[1], me->pos[0], me->pos[1]);
				if(p->path_size != 0 && p->path_size < 10){
					mon->path_to_player = p;
					mon->last_pc_pos[0] = me->pos[0];
					mon->last_pc_pos[1] = me->pos[1];
				}
			}
			if(mon->path_to_player != NULL){
				point next_move = *((mon -> path_to_player)+1);
				if(next_move.n_x > 159 || next_move.n_y > 95 || mon->path_to_player->path_size==1){
					check_monster_at_player(mon);
				}
				else if(current.layout[next_move.n_y][next_move.n_x].type == tile_type_floor){
					move_monster(mon, next_move.n_y-mon->pos[0], next_move.n_x-mon->pos[1]);
				}
			}
			*/
			if((mon->pos[0] < me->pos[0]+10 && mon->pos[0] > me->pos[0]-10) || (mon->pos[1] < me->pos[1]+10 && mon->pos[1] > me->pos[1]-10)){
				int c_y = mon->pos[0];
				int c_x = mon->pos[1];
				if(mon->pos[0] < me->pos[0] && mon->pos[1] < me->pos[1]){ //Move Right, then Down
					if(current.layout[c_y+1][c_x+1].type == tile_type_floor) move_monster(mon, 1, 1);
					else if(current.layout[c_y][c_x+1].type == tile_type_floor) move_monster(mon, 0, 1);
					else if(current.layout[c_y+1][c_x].type == tile_type_floor) move_monster(mon, 1, 0);
					else move_monster(mon,y,x);
				}
				else if(mon->pos[0] > me->pos[0] && mon->pos[1] < me->pos[1]){ //Move Left, then Down
					if(current.layout[c_y+1][c_x+1].type == tile_type_floor) move_monster(mon, -1, 1);
					else if(current.layout[c_y][c_x+1].type == tile_type_floor) move_monster(mon, 0, 1);
					else if(current.layout[c_y+1][c_x].type == tile_type_floor) move_monster(mon, -1, 0);
					else move_monster(mon,y,x);
				}
				else if(mon->pos[0] < me->pos[0] && mon->pos[1] > me->pos[1]){ //Move Right, then Up
					if(current.layout[c_y+1][c_x+1].type == tile_type_floor) move_monster(mon, 1, -1);
					else if(current.layout[c_y][c_x+1].type == tile_type_floor) move_monster(mon, 0, -1);
					else if(current.layout[c_y+1][c_x].type == tile_type_floor) move_monster(mon, 1, 0);
					else move_monster(mon,y,x);
				}
				else { //Move Left, then Up
					if(current.layout[c_y+1][c_x+1].type == tile_type_floor) move_monster(mon, -1, -1);
					else if(current.layout[c_y][c_x+1].type == tile_type_floor) move_monster(mon, 0, -1);
					else if(current.layout[c_y+1][c_x].type == tile_type_floor) move_monster(mon, -1, 0);
					else move_monster(mon,y,x);
				}
			}
			else{
				move_monster(mon, y, x);
			}
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
			if(current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].mon){
				Monster* moved_mon = current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].mon;
				moved_mon->pos[0] = c->pos[0];
				moved_mon->pos[1] = c->pos[1]; 
				current.layout[moved_mon->pos[0]][moved_mon->pos[1]].mon = moved_mon;
				}
			
			if(current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].pc){
				PC* pc = current.layout[(c->pos[0])+d_y][(c->pos[1])+d_x].pc;
				//pc -> alive = 0;
				do_battle(c);
				return;
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
		
		if(current.layout[y][x+1].pc) do_battle(mon);
		if(current.layout[y][x-1].pc) do_battle(mon);
		if(current.layout[y+1][x].pc) do_battle(mon);
		if(current.layout[y-1][x].pc) do_battle(mon);
		if(current.layout[y+1][x+1].pc) do_battle(mon);
		if(current.layout[y+1][x-1].pc) do_battle(mon);
		if(current.layout[y-1][x+1].pc) do_battle(mon);
		if(current.layout[y-1][x-1].pc) do_battle(mon);
	}
	
	int game::user_move(display disp){
		me->priority += pc_speed;
		turn++;
		
		int status_flag = 1;
		char sys_input = 0;
		
		while(status_flag == 1){
			sys_input = getchar();
			status_flag = interpret_input(sys_input);

			if(status_flag == 0){
				disp.AYS_prompt();
				char choice = getchar();
				if(choice == 'n') status_flag = 1;
				save_game();
				if(status_flag == 0) return 0;
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
			else if(status_flag == 14){
				disp.draw_backpack_menu(me, 1);
				int exit_menu = 0;
				while(!exit_menu){
					char choice = getchar();
					if(choice == 27) exit_menu = 1;
					else if(choice >= '0' && choice <= '9'){
						exit_menu = 1;
					}
				}
				status_flag = 1;
			}
			else if(status_flag == 15){
				disp.draw_equip_menu(me, 1);
				int exit_menu = 0;
				while(!exit_menu){
					char choice = getchar();
					if(choice == 27) exit_menu = 1;
					else if(choice >= 'a' && choice <= 'l'){
						exit_menu = 1;
					}
				}
				status_flag = 1;
			}
			else if(status_flag == 16){
				disp.draw_backpack_menu(me, 2);
				int exit_menu = 0;
				while(!exit_menu){
					char choice = getchar();
					if(choice == 27) exit_menu = 1;
					else if(choice >= '0' && choice <= '9'){
						int item = choice - 48;
						if(item < me->backpack.size() && current.layout[me->pos[0]][me->pos[1]].obj == NULL){
							Object* temp = me->backpack[item];
							me->backpack.erase((me->backpack.begin())+item);
							current.layout[me->pos[0]][me->pos[1]].obj = temp;
							exit_menu = 1;
						}
						else if(current.layout[me->pos[0]][me->pos[1]].obj){
							disp.prompt("There is already an object where you're standing. Drop it elsewhere.");
							getchar();
							disp.draw_backpack_menu(me, 2);
						}
					}
				}
				status_flag = 1;
			}
			else if(status_flag == 17){
				disp.draw_backpack_menu(me, 3);
				int exit_menu = 0;
				while(!exit_menu){
					char choice = getchar();
					if(choice == 27) exit_menu = 1;
					else if(choice >= '0' && choice <= '9'){
						int item = choice - 48;
						if(item < me->backpack.size()){
							Object* temp = me->backpack[item];
							me->backpack.erase((me->backpack.begin())+item);
							delete temp;
							exit_menu = 1;
						}
					}
				}
				status_flag = 1;
			}
			else{

			}
			disp.redraw_with_templates(current.layout, me);
		}
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
		else if(input == wear_item) return 14;
		else if(input == remove_equip) return 15;
		else if(input == drop_item) return 16;
		else if(input == remove_item) return 17;
		else return 1;
	}
	
	int game::do_battle(Monster* m){
		int dam2me = m->Damage->roll();
		int dam2mon = me->Damage->roll();

		if(me->equips.weapon){
			dam2mon += me->equips.weapon->Damage->roll();
		}

		me->HP -= dam2me;
		m->HP -= dam2mon;

		if(me->HP <= 0){
			me->alive = 0;
		}
		if(m->HP <= 0){
			m->alive = 0;
			current.layout[m->pos[0]][m->pos[1]].mon = NULL;
		}

		//disp.ticker_line("Fight Occured.");
	}