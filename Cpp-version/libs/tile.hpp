#ifndef TILE_HPP
#define TILE_HPP

#include "character.hpp"
#include "object.hpp"

class tile{
	public:
		char type; // All valid tile types have been moved to defs.h
		int hardness; // Hardness values are 0-9. 0 represents a floor already made and 9 is immutable.
		int is_room; // Used to determine is the tile is part of a room.
		PC* pc; // Used if a player is on the current tile
		Monster* mon; // Used if a monster is on the current tile
		Object* obj;
};

#endif