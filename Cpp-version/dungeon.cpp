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
#include "libs/char_template.hpp"
#include "libs/obj_template.hpp"

int main(int argc, char **argv)
{
	parser parser_system;
	srand(time(NULL)); //Used for time-based random number generation.
	
	if(argc == 3) {
		
		int mons = atoi(argv[1]);
		int objs = atoi(argv[2]);
		game* current_game = new game(mons, objs);
		display disp;
		int endflag = 1;
		int turn_status = 1;
		
		
		disp.init_display();
		disp.redraw_with_templates(current_game->current.layout, current_game->me);
		while(endflag == 1){
			turn_status = 1;
			endflag = current_game->user_move();
			while(turn_status == 1){
				turn_status = current_game->turn_system();
				if(turn_status == -1) endflag = 0;
			}
			disp.redraw_with_templates(current_game->current.layout, current_game->me);
		}

		disp.end_session();
		
		delete current_game;
		return 0;
	}
	else if(argc == 2){
		if(argv[1] == "-m"){
			std::cout << "Parsing the Monster Definitions located in " << defs_filename << '\n';
			std::vector<Char_template*> mon_defs = parser_system.parse_defs_file();
			if(mon_defs.size() == 0){
				std::cout << "Either there were no defs in the file or the file doesn't exist." << '\n';
				std::cout << "Please make sure that the file exists." << '\n';
			}
			else{
				std::cout << '\n';
				parser_system.output_mon_defs(mon_defs);
			}
			
			parser_system.kill_mon_defs(mon_defs);
		}
		else if(argv[1] == "-o"){
			std::cout << "Parsing the Object Definitions located in " << objs_filename << '\n';
			std::vector<Obj_template*> obj_defs = parser_system.parse_objs_file();
			if(obj_defs.size() == 0){
				std::cout << "Either there were no defs in the file or the file doesn't exist." << '\n';
				std::cout << "Please make sure that the file exists." << '\n';
			}
			else{
				std::cout << '\n';
				parser_system.output_obj_defs(obj_defs);
			}
			
			parser_system.kill_obj_defs(obj_defs);
		}
		else if(argv[1]== "-h"){
			std::cout << "RLG229 Game v. 1.09\n";
			std::cout << "Command Args:\n";
			std::cout << "-h = Displays this help text.";
			std::cout << "-m = Monster Def Parser Test\n";
			std::cout << "-o = Object Def Parser Test\n";
			std::cout << "<num1> <num2> = Run Game with num1 Monsters and num2 Objects\n";
		}
		else {
			std::cout << "Invalid Argument.";
		}
	}
	else{
		game* current_game = new game(default_num_mon, 10);
		display disp;
		int endflag = 1;
		int turn_status = 1;
		
		
		disp.init_display();
		disp.redraw_with_templates(current_game->current.layout, current_game->me);
		while(endflag == 1){
			turn_status = 1;
			endflag = current_game->user_move();
			while(turn_status == 1){
				turn_status = current_game->turn_system();
				if(turn_status == -1) endflag = 0;
			}
			disp.redraw_with_templates(current_game->current.layout, current_game->me);
		}

		disp.end_session();
		
		delete current_game;
		return 0;
	}
}

