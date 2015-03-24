/*
 * dungeon-main.cpp - The main running file for my Dungeon Crawler.
 * 
 * 
 * 
 */


#include <iostream>
#include <ctime>
#include <cstdlib>
#include "libs/map.hpp"

int main(int argc, char **argv)
{
	srand(time(NULL));
	map* current_map = new map();
	int num_mon = 10;
	
	std::cout << "Almost Done\n";
	delete current_map;
	return 0;
}

