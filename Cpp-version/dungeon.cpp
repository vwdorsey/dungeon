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
	game* current_game = new game(); 
	display disp;
	
	disp.init_display();
	disp.redraw(current_game->current.layout, current_game->me);
	while(getchar() != 27){}
	
	disp.end_session();
	delete current_game;
	return 0;
}

