#ifndef GAME_HPP
#define GAME_HPP

#include <cstdint>
#include "dijkstra.hpp"

class game{
	public:
		game(int npcs);
		~game();
	
		map current;
		Player* me;
		Monster* mon_list;
		pqueue turn_queue;
		int num_npcs;
		
		void save_game();
		void load_game();
		void change_floor();
		int turn_system();
		
		int user_move();
		int interpret_input(char input);
	private:
		struct cell{
			uint8_t open; //0 = open, else 255.
			uint8_t room_v; //255 = room, else 0.
			uint8_t corridor; //255 = corridor, else 0;
			uint8_t hardness; //Varies on space.
			uint8_t stair; //0 if no, 1 if down, 2 if up.
		};
		
		struct npc_data{
			char sprite;
			uint8_t position[2]; //x,y format
			uint8_t speed;
			uint8_t intelligence;
			uint8_t telepathy;
			uint8_t last_pc_pos[2]; //x,y format. 255 for both if not found
			uint32_t sequence;
			uint32_t next_turn;
			uint8_t reserved[20];
		};
		
		struct game_data{
			uint32_t save_version;
			uint32_t filesize;
			uint32_t eof;
			cell map[columns][rows]; //Will write on save.
			uint16_t num_rooms;
			//Room Data is in Map already.
			uint8_t pc_position[2]; //x,y format
			uint32_t turn;
			uint32_t sequence; //What the hell is this sequence number?
			uint16_t num_npcs;
			//Due to num_npcs being dynamic, the npc list will have to be generated on save.
		};
		
		void move_player(int d_y, int d_x);
		void move_monster(Monster *mon, int d_y, int d_x);
		void determine_mon_next_move(Monster *mon);
		void check_monster_at_player(Monster *mon);
		
		std::uniform_int_distribution<int> rand_mon_move;
		std::default_random_engine random;
		
		int mode; //0 for Control, 1 for Look
};

#endif
