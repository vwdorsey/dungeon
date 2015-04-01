/*
 * dungeon.cpp - The main running file for my Dungeon Crawler.
 * 
 */


#include <iostream>
#include <ctime>
#include <cstdlib>
#include "libs/game.hpp"
#include "libs/display.hpp"
#include "libs/parser.hpp"

int main(int argc, char **argv)
{
	if(argc > 1) {
	srand(time(NULL)); //Used for time-based random number generation.
	game* current_game = new game(default_num_mon); 
	display disp;
	int endflag = 1;
	int turn_status = 1;
	
	disp.init_display();
	disp.redraw(current_game->current.layout, current_game->me);
	while(endflag == 1){
		turn_status = 1;
		endflag = current_game->user_move();
		while(turn_status == 1){
			turn_status = current_game->turn_system();
			if(turn_status == -1) endflag = 0;
		}
		disp.redraw(current_game->current.layout, current_game->me);
	}
	
	disp.end_session();
	std::cout << current_game->turn;
	std::cout << '\n';
	std::cout << current_game->mon_turns;
	std::cout << '\n';
	std::cout << current_game->num_npcs;
	std::cout << '\n';
	std::cout << (int)current_game->me->alive;
	std::cout << '\n';
	std::cout << current_game->turn_queue.get_size();
	std::cout << '\n';
	delete current_game;
	return 0;
	}
	else {
		parser parser_system;
		std::cout << "Parsing the Monster Definitions located in " << defs_filename << '\n';
		std::vector<mon_template> mon_defs = parser_system.parse_defs_file();
		if(mon_defs.size() == 0){
			std::cout << "Either there were no defs in the file or the file doesn't exist." << '\n';
			std::cout << "Please make sure that the file exists." << '\n';
		}
		else{
			std::cout << '\n';
			parser_system.output_mon_defs(mon_defs);
		}
	}
}

