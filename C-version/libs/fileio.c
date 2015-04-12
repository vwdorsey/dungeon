/*
 * fileio.c - Deals with the file operations of saving/loading maps.
 * 
 * Copyright 2015 Vaughn Dorsey <vaughn@lr-jupiter>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "tile.h"
#include "room.h"
#include "endian.h"

typedef struct cell{
	unsigned char is_open; //If tile is a floor tile
	unsigned char is_room; //Stores if tile is part of room or not.
	unsigned char is_corridor; //Stores if part of a hallway
	unsigned char hardness; //Stores hardness.
	unsigned char stairs; //Stores if tile is a staircase or not.
} cell;

/*
 * write_save_file: The file saving function
 * 
 * Basically, this follows the process described in the README.
 * This process is listed under the '--save' switch
 * 
 */
void write_save_file(t_tile *map, roominfo *rooms){
	char filetype[6] = "RLG229";
	int version = 0;
	int filesize;
	cell map_info[15360];
	short num_rooms;
	int i = 0;
	int j = 0;
	
	char* home;
	char* path;
	char* savepath;
	FILE* save;
	
	while((rooms[i].x_start > 0) && i < 20){
		num_rooms++;
		i++;
	}
	
	/*
	 * This is the tile to cell conversion process.
	 * 
	 * How it works:
	 * 		For Barrier/Type 0:
	 * 			- hardness is set to 255 (immutable)
	 * 			- is_open, is_room, and is_corridor are set to zero
	 * 
	 * 		For Rocks/Type 1:
	 * 			- hardness is set to the tile's hardness value multiplied by 28
	 * 			- is_open, is_room, and is_corridor are set to zero
	 * 
	 * 		For Walls/Type 2:
	 * 			- hardness is set to the tile's hardness value multiplied by 28
	 * 			- is_room or is_corridor is set to 255, depending on the value of the tile's is_room 
	 * 			- is_open is set to zero
	 * 
	 * 		For Floors/Type 3:
	 * 			- is_open is set to 1
	 * 			- hardness is set to zero.
	 * 			- is_room or is_corridor is set to 255, depending on the value of the tile's is_room 
	 * 
	 */
	for(i = 0; i < 96; i++){
		for(j = 0; j < 160; j++){
			if(get_type(map+((j)+((i)*160))) == 0){ // Barrier
				map_info[j+(i*160)].is_open = 0;
				map_info[j+(i*160)].is_room = 0;
				map_info[j+(i*160)].is_corridor = 0;
				map_info[j+(i*160)].hardness = 255;
				map_info[j+(i*160)].stairs = 0;
			}
			else if(get_type(map+((j)+((i)*160))) == 1){ // Rock
				map_info[j+(i*160)].is_open = 0;
				map_info[j+(i*160)].is_room = 0;
				map_info[j+(i*160)].is_corridor = 0;
				map_info[j+(i*160)].hardness = ((map+((j)+((i)*160)))->hardness) * 28;
				map_info[j+(i*160)].stairs = 0;
			}
			else if(get_type(map+((j)+((i)*160))) == 2){ // Wall
				map_info[j+(i*160)].is_open = 0;
				if((map+((j)+((i)*160)))->is_room){
					map_info[j+(i*160)].is_room = 255;
					map_info[j+(i*160)].is_corridor = 0;
				}
				else{
					map_info[j+(i*160)].is_room = 0;
					map_info[j+(i*160)].is_corridor = 255;
				}
				map_info[j+(i*160)].hardness = ((map+((j)+((i)*160)))->hardness) * 28;
				map_info[j+(i*160)].stairs = 0;
			}
			else{	// Path
				map_info[j+(i*160)].is_open = 1;
				if((map+((j)+((i)*160)))->is_room){
					map_info[j+(i*160)].is_room = 255;
					map_info[j+(i*160)].is_corridor = 0;
				}
				else{
					map_info[j+(i*160)].is_room = 0;
					map_info[j+(i*160)].is_corridor = 255;
				}
				map_info[j+(i*160)].hardness = 0;
				map_info[j+(i*160)].stairs = 0;
			}
			if((map+((j)+((i)*160))).type == tile_type_upstair;){
					map_info[j+(i*160)].is_open = 0;
					map_info[j+(i*160)].is_room = 0;
					map_info[j+(i*160)].is_corridor = 0;
					map_info[j+(i*160)].hardness = 0;
					map_info[j+(i*160)].stairs = 1;
				}
			if((map+((j)+((i)*160))).type == tile_type_downstair;){
					map_info[j+(i*160)].is_open = 0;
					map_info[j+(i*160)].is_room = 0;
					map_info[j+(i*160)].is_corridor = 0;
					map_info[j+(i*160)].hardness = 0;
					map_info[j+(i*160)].stairs = 2;
				}
		}
	}
	
	filesize = 15360*4 + num_rooms * 4;
	
	filesize = htobe32(filesize);
	version = htobe32(filesize);
	num_rooms = htobe16(num_rooms);
	
	home = getenv("HOMEPATH"); //This should work for Windows machines.
	
	if (home == NULL){
		home = getenv("HOME"); //This definitely works for Linux.
	}
	
	path = malloc(strlen(home) + strlen(".rlg229/") + 4);
	sprintf(path, "%s/%s", home, ".rlg229/");
	mkdir(path, S_IRWXU);
	
	savepath = malloc(strlen(path) + strlen("dungeon") + 4);
	sprintf(savepath, "%s%s", path, "dungeon");
	
	save = fopen(savepath, "w");
	
	fwrite(&filetype, sizeof(filetype[0]), 6 , save);
	fwrite(&version, sizeof(version), 1, save);
	fwrite(&filesize, sizeof(filesize), 1, save);
	for(i = 0; i < 15360; i++){
		fwrite(&map_info[i].is_open, sizeof(map_info[i].is_open), 1, save);
		fwrite(&map_info[i].is_room, sizeof(map_info[i].is_room), 1, save);
		fwrite(&map_info[i].is_corridor, sizeof(map_info[i].is_corridor), 1, save);
		fwrite(&map_info[i].hardness, sizeof(map_info[i].hardness), 1, save);
	}
	fwrite(&num_rooms, sizeof(num_rooms), 1, save);
	for(i = 0; i < num_rooms; i++){
		fwrite(&rooms[i].x_start, sizeof(rooms[i].x_start), 1, save);
		fwrite(&rooms[i].y_start, sizeof(rooms[i].y_start), 1, save);
		fwrite(&rooms[i].x_dim, sizeof(rooms[i].x_dim), 1, save);
		fwrite(&rooms[i].y_dim, sizeof(rooms[i].y_dim), 1, save);
	}
	
	
	fclose(save);

	free(savepath);
	free(path);
}

/*
 * read_load_file: The file loading function
 * 
 * Basically, this follows the process described in the README.
 * This process is listed under the '--load' switch
 * 
 */
void read_load_file(t_tile *loaded_map, roominfo *rooms){
	char filetype[6];
	int version;
	int filesize;
	cell map_info[15360];
	short num_rooms;
	int i = 0;
	int j = 0;
	
	char* home;
	char* path;
	char* savepath;
	FILE* load;
	
	home = getenv("HOMEPATH"); //This should work for Windows machines.
	
	if (home == NULL){
		home = getenv("HOME"); //This definitely works for Linux.
	}
	
	path = malloc(strlen(home) + strlen(".rlg229/") + 4);
	sprintf(path, "%s/%s", home, ".rlg229/");
	mkdir(path, S_IRWXU);
	
	savepath = malloc(strlen(path) + strlen("dungeon") + 4);
	sprintf(savepath, "%s%s", path, "dungeon");
	
	load = fopen(savepath, "r");
	
	fread(&filetype, sizeof(char), 6, load);
	
	
	fread(&version, sizeof(int), 1, load);
	version = be32toh(version);
	
	fread(&filesize, sizeof(int), 1, load);
	filesize = be32toh(filesize);
	
	for(i = 0; i < 15360; i++){
		fread(&map_info[i].is_open, sizeof(char), 1, load);
		fread(&map_info[i].is_room, sizeof(char), 1, load);
		fread(&map_info[i].is_corridor, sizeof(char), 1, load);
		fread(&map_info[i].hardness, sizeof(char), 1, load);
	}
	
	fread(&num_rooms, sizeof(short), 1, load);
	num_rooms = be16toh(num_rooms);
	
	for(i = 0; i < num_rooms; i++){
		fread(&rooms[i].x_start, sizeof(rooms[i].x_start), 1, load);
		fread(&rooms[i].y_start, sizeof(rooms[i].y_start), 1, load);
		fread(&rooms[i].x_dim, sizeof(rooms[i].x_dim), 1, load);
		fread(&rooms[i].y_dim, sizeof(rooms[i].y_dim), 1, load);
	}
	
	fclose(load);
	
	free(savepath);
	free(path);
	/*
	 * This is the cell to tile conversion process
	 * 
	 * How it works:
	 * 		If the current cell has a hardness of 255, it's a barrier. Set it as such
	 * 		If the current cell has a is_open value of 1, it's a floor tile. Set it as such
	 * 		If the current cell has a is_room or is_corridor value of 255, it's a wall. Set it as such.
	 * 		Else, the cell must be a rock/unfilled space. Set it as such.
	 */
	for(i = 0; i < 96; i++){
		for(j = 0; j < 160; j++){
			if(map_info[j+(i*160)].hardness == 255){ // Barrier
				set_type(loaded_map+((j)+((i)*160)), 0);
				(loaded_map+((j)+((i)*160)))->hardness = 9;
				(loaded_map+((j)+((i)*160)))->is_room = 0;
			}
			else if(map_info[j+(i*160)].is_open == 1){ // A path
				set_type(loaded_map+((j)+((i)*160)), 3);
				(loaded_map+((j)+((i)*160)))->hardness = 0;
				(loaded_map+((j)+((i)*160)))->is_room = 0;
			}
			else if(map_info[j+(i*160)].is_room != 0 || map_info[j+(i*160)].is_corridor != 0){ // Wall
				set_type(loaded_map+((j)+((i)*160)), 2);
				(loaded_map+((j)+((i)*160)))->hardness = ((map_info[j+(i*160)].hardness)/28);
				if(map_info[j+(i*160)].is_room == 255) (loaded_map+((j)+((i)*160)))->is_room = 1;
				else (loaded_map+((j)+((i)*160)))->is_room = 0;
			}
			else{ // Rock
				set_type(loaded_map+((j)+((i)*160)), 1);
				(loaded_map+((j)+((i)*160)))->hardness = ((map_info[j+(i*160)].hardness)/28);
				(loaded_map+((j)+((i)*160)))->is_room = 0;
			}
		}
	}
}

