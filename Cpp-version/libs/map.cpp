/*
 * map.cpp - Contains all the classes and functions necessary to 
 * create and maintain a map for the dungeon crawler
 * 
 */


#include <iostream>
#include <cstdlib>
#include <random>
#include "values.hpp"
#include "map.hpp"
#include "dijkstra.hpp"

map::map(){
	room_count = min_rooms + (random() % ((max_rooms - min_rooms) + 1));
	
	random.seed(rand());
	column_dist = std::uniform_int_distribution<int>(0, columns);
	row_dist = std::uniform_int_distribution<int>(0, rows);
	
	init_map();
	place_rooms();
	determine_paths();
	
	design_output();
	}

map::~map(){
	//std::cout << "Goodbye\n";
	}

void map::init_map(){
	int x = 0;
	int y = 0;
	
	for(y = 0; y < columns; y++){
		for(x = 0; x < rows; x++){
			if(y == 0 || y == columns-1){
				layout[y][x].type = tile_type_immutable;
				layout[y][x].hardness = 9;
			}
			else if(x == 0 || x == rows-1){
				layout[y][x].type = tile_type_immutable;
				layout[y][x].hardness = 9;
			}
			else{
				layout[y][x].type = tile_type_empty;
				layout[y][x].hardness = (rand() % 8) + 1;
			}
		}
	}
}

void map::design_output(){
	int x = 0;
	int y = 0;
	
	for(y = 0; y < columns; y++){
		for(x = 0; x < rows; x++){
			std::cout << layout[y][x].type;
		}
		std::cout << '\n';
	}
}

void map::place_rooms(){
	int i = 0;
	std::uniform_int_distribution<int> room_x(min_room_x, max_room_x);
	std::uniform_int_distribution<int> room_y(min_room_y, max_room_y);
	
	while(i < room_count) {
		int start_y = column_dist(random);
		int start_x = row_dist(random);
		int y_dim = room_y(random);
		int x_dim = room_x(random);
		
		if(layout[start_y][start_x].type == tile_type_empty){
			if(check_room_placement(y_dim, x_dim, start_y, start_x) == 0){
				for(int j = 0; j < y_dim+1; j++){
					for(int k = 0; k < x_dim+1; k++){
						if(j == 0 || j == y_dim){
							layout[start_y+j][start_x+k].type = tile_type_wall;
							layout[start_y+j][start_x+k].is_room = 1;
						}
						else if(k == 0 || k == x_dim){
							layout[start_y+j][start_x+k].type = tile_type_wall;
							layout[start_y+j][start_x+k].is_room = 1;
						}
						else{
							layout[start_y+j][start_x+k].type = tile_type_floor;
							layout[start_y+j][start_x+k].is_room = 1;
							layout[start_y+j][start_x+k].hardness = 0;
						}
					}
				}
				
				room_info[i].x_dim = x_dim;
				room_info[i].y_dim = y_dim;
				room_info[i].x_start = start_x;
				room_info[i].y_start = start_y;
				
				i++;
			}
		}
	}
}

char map::check_room_placement(int y_dim, int x_dim, int y, int x){
	for(int i = 0; i < y_dim; i++){
		if(x+i > 152 || x+i < 6) return -1;
		for(int j = 0; j < x_dim; j++){
			if(y+j > 91|| y+j < 5) return -1;
			if(layout[y+i][x+j].type != tile_type_empty) return -1;
			if(layout[y+i+4][x+j].type != tile_type_empty) return -1;
			if(layout[y+i-4][x+j].type != tile_type_empty) return -1;
			if(layout[y+i][x+j+4].type != tile_type_empty) return -1;
			if(layout[y+i][x+j-4].type != tile_type_empty) return -1;
			if(layout[y+i+4][x+j+4].type != tile_type_empty) return -1;
			if(layout[y+i-4][x+j+4].type != tile_type_empty) return -1;
			if(layout[y+i+4][x+j-4].type != tile_type_empty) return -1;
			if(layout[y+i-4][x+j-4].type != tile_type_empty) return -1;
		}
	}
	return 0;
	}
		
void map::determine_paths(){
	for(int i = 0; i < room_count-1; i++){
		int src_panel_select = (rand() % 2)+1;
		int src_x, src_y, des_x, des_y;
                
		if(src_panel_select == 1){ //Right Panel
			src_y = (room_info[i].y_start + 2 + (rand() % (room_info[i].y_dim)/2));
			src_x = (room_info[i].x_start - 1 + room_info[i].x_dim);
			
		}
		else{ //Left Panel
			src_y = (room_info[i].y_start + 2 + (rand() % (room_info[i].y_dim)/2));
			src_x = (room_info[i].x_start);
		}
		
		des_x = (room_info[i+1].x_start + (room_info[i+1].x_dim / 2));
		des_y = (room_info[i+1].y_start + (room_info[i+1].y_dim / 2));
		generate_corridors(src_y, src_x, src_panel_select, des_y, des_x);
		
	}
}
		
void map::generate_corridors(int s_y, int s_x, int src_pnl, int d_y, int d_x){
	dijkstra paths;
	int cur_x = s_x;
	int cur_y = s_y;
	int i;
	
	for(i = 0; i < 3; i++){
		
		if(src_pnl == 1){ //right side
			if (i != 0) cur_x++;
			layout[cur_y][cur_x].type = tile_type_immutable;
			if(layout[cur_y+1][cur_x].type == tile_type_empty) layout[cur_y+1][cur_x].type = tile_type_wall;
			if(layout[cur_y][cur_x-1].type == tile_type_empty) layout[cur_y][cur_x-1].type = tile_type_wall;
			if(layout[cur_y+1][cur_x+1].type == tile_type_empty) layout[cur_y+1][cur_x+1].type = tile_type_wall;
			if(layout[cur_y][cur_x+1].type == tile_type_empty) layout[cur_y][cur_x+1].type = tile_type_wall;
			if(layout[cur_y-1][cur_x+1].type == tile_type_empty) layout[cur_y-1][cur_x+1].type = tile_type_wall;
		}
		
		else{ //left side
			if (i != 0) cur_x--;
			layout[cur_y][cur_x].type = tile_type_immutable;
			if(layout[cur_y-1][cur_x].type == tile_type_empty) layout[cur_y-1][cur_x].type = tile_type_wall;
			if(layout[cur_y][cur_x-1].type == tile_type_empty) layout[cur_y][cur_x-1].type = tile_type_wall;
			if(layout[cur_y-1][cur_x-1].type == tile_type_empty) layout[cur_y-1][cur_x-1].type = tile_type_wall;
			if(layout[cur_y][cur_x+1].type == tile_type_empty) layout[cur_y][cur_x+1].type = tile_type_wall;
			if(layout[cur_y-1][cur_x+1].type == tile_type_empty) layout[cur_y-1][cur_x+1].type = tile_type_wall;
			/* 
			if (i != 0) cur_x--;
			set_type((t+((cur_y)+((cur_x)*160))), 3);
			if(get_type((t+((cur_y-1)+((cur_x)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x)*160))), 2);
			if(get_type((t+((cur_y)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x-1)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x-1)*160))), 2);
			if(get_type((t+((cur_y)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y)+((cur_x+1)*160))), 2);
			if(get_type((t+((cur_y-1)+((cur_x+1)*160)))) == 1) set_type((t+((cur_y-1)+((cur_x+1)*160))), 2);
			*/	
		}
	paths.Dijkstra(this->layout, s_y, s_x, d_y, d_x);
	
	}
	/*
	//Would like to replace this with a Dijkstra's method at some point. It'll make the pathways more random, I think.
	
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
	*/
}

