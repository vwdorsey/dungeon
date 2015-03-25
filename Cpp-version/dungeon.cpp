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
	int endflag = 0;
	
	disp.init_display();
	disp.redraw(current_game->current.layout, current_game->me);
	while(endflag == 0){
		char key = getchar();
		if(key == save_and_exit){
			current_game->save_game();
			endflag = 1;
			}
		} 
	
	disp.end_session();
	delete current_game;
	return 0;
}

