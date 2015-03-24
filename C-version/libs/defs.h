#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>

// Attributes Block
#define IS_SMART        1
#define TELEPATHIC      2
#define BIT2            4
#define BIT3            8
#define BIT4            16
#define BIT5            32
#define BIT6            64
#define BIT7            128
#define BIT8            256
#define BIT9            512
#define BIT10           1024
#define BIT11           2048
#define BIT12           4096
#define BIT13           8192
#define BIT14           16386
#define BIT15           32768

// Tilings
#define tile_type_wall      '+'
#define tile_type_empty     ' '
#define tile_type_immutable '#'
#define tile_type_floor     '.'
#define tile_type_upstair   '<'
#define tile_type_downstair '>'

// Map Settings
#define rows        160
#define columns     96
#define min_rooms   12
#define max_rooms   20
#define min_room_x  10
#define min_room_y  7
#define max_room_x  20
#define max_room_y  15
#define default_num_mon 10

typedef struct point{
    unsigned int n_x;  
    unsigned int n_y;
    unsigned int path_size;
} point;

typedef struct Monster{
    unsigned char Sprite;
    int pos[2];
    uint8_t speed;
    uint16_t attribs;
    point* path_to_player;
    unsigned char alive;
} Monster;

typedef struct Player{
    unsigned char Sprite;
    int pos[2];
    uint8_t speed;
    unsigned char alive;
    unsigned int priority;
} Player;

/*
	This struct is used as a tile information holder for any information about the tile.
	I expect this struct to expand in terms of variables stored inside.
*/
typedef struct tile{
	char type; // All valid tile types have been moved to defs.h
	int hardness; // Hardness values are 0-9. 0 represents a floor already made and 9 is immutable.
	int is_room; // Used to determine is the tile is part of a room.
	Player* pc; // Used if a player is on the current tile
    Monster* mon; // Used if a monster is on the current tile
} t_tile;

typedef struct dij_node{
	unsigned int x;
	unsigned int y;
    unsigned int cost;
	struct dij_node* previous;
} dij_node;

/*
	Struct to hold all of the necessary information about each room, including the dimensions and where the room starts.
	I expect this to expand later as more functionality is added to the code.
*/
typedef struct roominfo {
	unsigned char x_dim; //X dimension
	unsigned char y_dim; //Y dimension
	unsigned char x_start; //X start
	unsigned char y_start; //Y start
} roominfo;



#endif
