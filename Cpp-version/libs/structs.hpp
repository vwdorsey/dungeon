#ifndef STRUCTS_HPP
#define STRUCTS_HPP

/**
 * structs.hpp - Defines a number of structs carried over from the C version of this project.
 */
 
#include <string>
#include <vector>
#include <cstdint>
#include "values.hpp"

/*
 * 
 * Structs used for Dijkstra's Algorithm
 * 
 */

    typedef struct point{
        unsigned int n_x;  
        unsigned int n_y;
        unsigned int path_size;
    } point;

    typedef struct dij_node{
	unsigned int x;
	unsigned int y;
    unsigned int cost;
    unsigned int distance;
	struct dij_node* previous;
    } dij_node;



/*
 * 
 * Structs used for Characters.
 * 
 */ 

    struct Monster{
        unsigned char Sprite;
        int pos[2]; //y,x format
        uint8_t speed;
        uint16_t attribs;
        uint8_t last_pc_pos[2]; //y,x format
        point* path_to_player;
        unsigned char alive;
    };

    struct Player{
        unsigned char Sprite;
        int pos[2]; //y,x format
        uint8_t speed;
        unsigned char alive;
        unsigned int priority; //What was this being used for?
    };

/*
 * 
 * Structs used for the Map itself
 * 
 */
 
     /*
        This struct is used as a tile information holder for any information about the tile.
        I expect this struct to expand in terms of variables stored inside.
    */
    struct tile{
        char type; // All valid tile types have been moved to defs.h
        int hardness; // Hardness values are 0-9. 0 represents a floor already made and 9 is immutable.
        int is_room; // Used to determine is the tile is part of a room.
        Player* pc; // Used if a player is on the current tile
        Monster* mon; // Used if a monster is on the current tile
    };
    
    /*
	Struct to hold all of the necessary information about each room, including the dimensions and where the room starts.
	I expect this to expand later as more functionality is added to the code.
    */
    struct room{
        unsigned char x_dim; //X dimension
        unsigned char y_dim; //Y dimension
        unsigned char x_start; //X start
        unsigned char y_start; //Y start
    };
    
/*
 * Structs derived from the parser code.
 * 
 */ 

struct dice{
	int base; //Base Value
	int num_dice; //Number of Dice used
	int sides; //How many sides each die has.
};

struct mon_template{
	std::string Name; //Name of the monster
	char Sprite; //Monster Sprite
	std::string Color; //Color the monster should be displayed as
	std::vector<std::string> Description; //Must be no longer than 77 chars in width;
	uint16_t Attribs; //Attributes that the monster has
	dice* Speed; // Dice values for Speed
	dice* HP; // Dice values for HP
	dice* Damage; // Dice values for Damage/Attack
};

struct obj_template{
	std::string Name; 						//Name of the object
	std::vector<std::string> Description; 	//Must be no longer than 77 chars in width;
	uint32_t Type; 							//Object Type. Populated using a bitfield.
	std::string Color; 						//Color the Object should be displayed as
	dice* Hit; 								// Dice values for Hit Bonus
	dice* Damage; 							// Dice values for Damage/Attack Bonus
	dice* Dodge; 							// Dice values for Dodge/Evasion Bonus
	dice* Defense; 							// Dice values for Defense/Block Bonus given to Character
	dice* Weight; 							//Dice values for Weight of object.
	dice* Speed; 							//Dice values for Speed Bonus object gives to character
	dice* SpecAttr; 							//Dice values for A special attribute value for each object.
	dice* Value; 							//Dice values for Value of object in game in some currency.
};

#endif
