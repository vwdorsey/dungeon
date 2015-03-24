/*
 * generation.c - Dungeon Layout Generator
 * 
 * Copyright 2015 Vaughn <vaughn@CrunchDev>
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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tile.h"
#include "generation.h"
#include "room.h"
#include "math.h"

typedef struct tile t_tile;

int check_room_placement(t_tile *t, int x_dim, int y_dim, int x, int y);
void place_rooms(t_tile *t, roominfo *r);
void make_paths(t_tile *t, roominfo *r);
void generate_paths(t_tile *t, int source_x, int source_y, int source_panel, int dest_x, int dest_y);

/*
	Initializes the 160x96 map to have a immutable border around it and empty space in the rest of the map.
	It then calls the place_rooms and make_paths to fully generate a dungeon.
	The dungeon layout and room information are returned via a pointer for later use.
*/
void init_map(t_tile *t, roominfo *r){
	int x = 0;
	int y = 0; 
	
	for(x = 0; x < 96; x++){
		for(y = 0; y < 160; y++){
			if(x == 0 || x == 95){
				(t+(y+(x*160)))->hardness = 9; 
                            set_type((t+(y+(x*160))), 0);
				 
			 }
			else if(y == 0 || y == 159){
				(t+(y+(x*160)))->hardness = 9;
                            set_type((t+(y+(x*160))), 0);
				
			}
			else {
                            (t+(y+(x*160)))->hardness = ((rand() % 8) + 1);
				set_type((t+(y+(x*160))), 1);
				
			}
			(t+(y+(x*160)))->mon = NULL;
                        (t+(y+(x*160)))->pc = NULL;
		}
	}
	
	place_rooms(t, r);
	
	make_paths(t, r);
}

/*
	This is the entire room placement function.
	
	It works as follows: It first determines a number between 12 - 20 that will represent the number of rooms to be generated. If
	the random number generator gives something below 12, then the number of rooms is set at 12. Then, for each room that it must
	generate, it randomly attempts to find configurations of start locations and dimensions that will meet specifications and fit
	inside the empty area of the map. It checks the validity using the check_room_placement function, which makes sure that it is
	at least 5 spaces away from any non-empty location on the board. Once a layout is found, it then writes it to the map by 
	setting the types to floor/wall tiles and hardnesses to zero for floor tiles. Once the layout is generated, information about
	it is written to the roominfo array. This process continues until all rooms have been generated successfully. At the tail end,
	a final room is created with all -1 attributes so that parts of the program have a stop point.
*/
void place_rooms(t_tile *t, roominfo *r){
	int i = 0;
	int num_rooms = rand() % 21;
	
	if(num_rooms < 12) num_rooms = 12;
	
	while(i<num_rooms){
		int start_x = (rand() % 96);
		int start_y = (rand() % 160);
		
		int x_dim = 7 + (rand() % 9);
		int y_dim = 10 + (rand() % 11);
		
		if ((t+(start_y+(start_x*160)))->type == ' '){
			if(check_room_placement(t, x_dim, y_dim, start_x, start_y) == 0){
				int j, k;
				for(j = 0; j < x_dim; j++){
					for(k = 0; k < y_dim; k++){
						if(j == 0 || j == x_dim-1){
							set_type((t+((start_y+k)+((start_x+j)*160))), 2);
							(t+((start_y+k)+((start_x+j)*160)))->is_room = 1;
						}
						else if(k == 0 || k == y_dim-1){
							set_type((t+((start_y+k)+((start_x+j)*160))), 2);
							(t+((start_y+k)+((start_x+j)*160)))->is_room = 1;
						}
						else {
							set_type((t+((start_y+k)+((start_x+j)*160))), 3);
							(t+((start_y+k)+((start_x+j)*160)))->hardness = 0;
							(t+((start_y+k)+((start_x+j)*160)))->is_room = 1;
						}
					}
				}
				set_room_info(x_dim, y_dim, start_x, start_y, i, r);
				i++;
			}
		}
	}
	if(num_rooms < 20){
		i++;
		set_room_info(-1,-1,-1,-1,i,r);
	}
}

/*
	This checks to see if there is anything on the source, or 5 positions away from the source.
	It's a simple utility that cuts down on code.
*/
int check_room_placement(t_tile *t, int x_dim, int y_dim, int x, int y){
	int i, j;
	
	for(i = 0; i < x_dim; i++){
		if(x+i > 91 || x+i < 4) return -1;
		for(j = 0; j < y_dim; j++){
			if(y+j > 152) return -1;
			if(get_type((t+((y+j)+((x+i)*160)))) != 1) return -1;
			if(get_type((t+((y+j+4)+((x+i)*160)))) != 1) return -1;
			if(get_type((t+((y+j-4)+((x+i)*160)))) != 1) return -1;
			if(get_type((t+((y+j)+((x+i+4)*160)))) != 1) return -1;
			if(get_type((t+((y+j)+((x+i-4)*160)))) != 1) return -1;
			if(get_type((t+((y+j+4)+((x+i+4)*160)))) != 1) return -1;
			if(get_type((t+((y+j-4)+((x+i+4)*160)))) != 1) return -1;
			if(get_type((t+((y+j+4)+((x+i-4)*160)))) != 1) return -1;
			if(get_type((t+((y+j-4)+((x+i-4)*160)))) != 1) return -1;
		}
	}
	return 0;
}

/*
	This function sets up each path for generation and hands it off to generate_paths.
	
	It starts by enumerating the number of actual rooms in the roominfo struct. Once it has this, it starts at the first room,
	finding a random location on either the left or right side, again randomly selected, and recording this location. It then 
	sets a destination for the middle of the next room in the roominfo list. These variables, along with the tile array and 
	roominfo pointers, are passed to generate_paths to actually construct the path. It repeats this process until it reaches
	the second to last room, which will connect the last room to the grid, if it hasn't already.
	
	This code will not check to see if there is already an available path, instead just creating a direct path. This is to make 
	sure that there is always a path to something. It also adds some loops inside some of the rooms, depending on the layout of 
	the room.
*/
void make_paths(t_tile *t, roominfo *r){
	int num_rooms = 0;
	int i = 0;
	
	while((r[i].x_start > 0) && i < 20){
		num_rooms++;
		i++;
	}
	
	for(i = 0; i < num_rooms-1; i++){
		int src_panel_select = (rand() % 2)+1;
		int src_x, src_y, des_x, des_y;
                
		if(src_panel_select == 1){ //Right Panel
			src_x = (r[i].x_start + 2 + (rand() % (r[i].x_dim)/2));
			src_y = (r[i].y_start - 1 + r[i].y_dim);
			
		}
		else{ //Left Panel
			src_x = (r[i].x_start + 2 + (rand() % (r[i].x_dim)/2));
			src_y = (r[i].y_start);
		}
		
		des_x = (r[i+1].x_start + (r[i+1].x_dim / 2));
		des_y = (r[i+1].y_start + (r[i+1].y_dim / 2));
		generate_paths(t, src_x, src_y, src_panel_select, des_x, des_y);
		
	}
}

/*
	The actual code for generating paths.
	
	The algorithm it uses is as follows: First, upon calling the method, it creates a psuedo-cursor, which keeps track
	of where the path generator currently is looking. It then starts by making a short extension off of the source room,
	based on the side selected in make_paths and the random point selected on this side, again from make_paths. 
	
	After the extension is created, it then starts by looking at if the cursor x is above, below, or already on (rare) the
	destination x's value. If it (the cursor x) is greater or less than, then the code will draw a path, surrounded by walls
	if they are placeable, to the destination x. If it has to pass through anything, it will simply draw a path, but no walls.
	Once it reaches the correct x value, or if it's already there, it then draws straight left or right until it reaches the
	destination. Control then returns to make_paths.
	
	If I get a chance, I might want to take another look at this and see if I can improve the code any.
*/
void generate_paths(t_tile *t, int source_x, int source_y, int source_panel, int dest_x, int dest_y){
	int cur_x = source_x;
	int cur_y = source_y;
	int i;
	
	for(i = 0; i < 3; i++){
		
		if(source_panel == 1){ //right side
			if (i != 0) cur_y++;
			set_type((t+((cur_y)+((cur_x)*160))), 3);
			if(get_type((t+((cur_y+1)+((cur_x)*160)))) == 1) set_type((t+((cur_y+1)+((cur_x)*160))), 2);
			if(get_type((t+((cur_y)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y+1)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y+1)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y)+((cur_x+1)*160))), 2);
			if(get_type((t+((cur_y+1)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y+1)+((cur_x+1)*160))), 2);
		}
		else{ //left side
			if (i != 0) cur_y--;
			set_type((t+((cur_y)+((cur_x)*160))), 3);
			if(get_type((t+((cur_y-1)+((cur_x)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x)*160))), 2);
			if(get_type((t+((cur_y)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y)+((cur_x+1)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x+1)*160))), 2);	
		}
	}
	
	if(cur_x < dest_x){
		while(cur_x != dest_x){ //moves down
			cur_x++;
			set_type((t+((cur_y)+((cur_x-1)*160))), 3);
			set_type((t+((cur_y)+((cur_x)*160))), 3);
			if(get_type((t+((cur_y)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y)+((cur_x)*160))), 2);
			if(get_type((t+((cur_y+1)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y+1)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y+1)+((cur_x)*160)))) == 1) set_type((t+((cur_y+1)+((cur_x)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x)*160))), 2);
			if(get_type((t+((cur_y+1)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y+1)+((cur_x+1)*160))), 2);
			if(get_type((t+((cur_y)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y)+((cur_x+1)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x+1)*160))), 2);
		}
	}
	else{
		while(cur_x != dest_x){ //moves up
			cur_x--;
			set_type((t+((cur_y)+((cur_x)*160))), 3);
			if(get_type((t+((cur_y)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y+1)+((cur_x)*160)))) == 1) set_type((t+((cur_y+1)+((cur_x)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x)*160))), 2);
			if(get_type((t+((cur_y+1)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y+1)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x-1)*160))), 2);
		}
	}
	if(cur_y < dest_y){ 
		while(cur_y != dest_y){
			cur_y++;
			set_type((t+((cur_y)+((cur_x)*160))), 3);
			if(get_type((t+((cur_y)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y+1)+((cur_x)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x+1)*160))), 2);
			if(get_type((t+((cur_y)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y)+((cur_x+1)*160))), 2);
		}
	}
	else{
		while(cur_y != dest_y){ 
			cur_y--;
			set_type((t+((cur_y)+((cur_x)*160))), 3);
			if(get_type((t+((cur_y-1)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x)*160))), 2);
			if(get_type((t+((cur_y-2)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y-2)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y)+((cur_x+1)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x+1)*160))), 2);
		}
	}
}

/*
	Simply put, this is just something that makes outputting a design far easier.
*/
void design_output(t_tile *t){
	int x = 0;
	int y = 0;
	
	for(x = 0; x < 96; x++){
		for(y = 0; y < 160; y++){
                    if((t+(y+(x*160)))->mon != NULL) printf("%c", (t+(y+(x*160)))->mon->Sprite);
                    else if((t+(y+(x*160)))->pc != NULL) printf("%c", (t+(y+(x*160)))->pc->Sprite);
                    else printf("%c", (t+(y+(x*160)))->type);
			//Line below is used for debugging and being able to see the hardness numbers.
			//printf("%d", (t+(y+(x*160)))->hardness); 
		}
		printf("\n");
	}
}
