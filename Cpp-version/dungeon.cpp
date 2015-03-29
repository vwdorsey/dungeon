/*
 * dungeon.cpp - The main running file for my Dungeon Crawler.
 * 
 */


#include <iostream>
#include <ctime>
#include <cstdlib>
#include "libs/game.hpp"
#include "libs/display.hpp"

int main(int argc, char **argv)
{
	srand(time(NULL)); //Used for time-based random number generation.
	game* current_game = new game(default_num_mon); 
	display disp;
	int endflag = 1;
	int turn_status = 1;
	
	disp.init_display();
	disp.redraw(current_game->current.layout, current_game->me);
	while(endflag == 1){
		endflag = current_game->user_move();
		while(turn_status){
			turn_status = current_game->turn_system();
		}
		disp.redraw(current_game->current.layout, current_game->me);
	}
	
	disp.end_session();
	delete current_game;
	return 0;
}

