/*
 * dungeon-main.c: Main running file for my Dungeon Crawler.
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


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "libs/tile.h"
#include "libs/generation.h"
#include "libs/fileio.h"
#include "libs/path.h"
#include "libs/game.h"
#include "libs/queue.h"
#include "libs/defs.h"
#include "libs/display.h"
#include <ncurses.h>

void interpret_key(char ch, int* d_y, int* d_x, int* status);

/*
	The main method for my game. Currently, it has the following functionality:
		- (1.01) Map Initialization, with room and path placements
		- (1.01) Ability to output the current floor design.
		- (1.02) Ability to save/load a dungeon from file.
                - (1.03) Generate shortest paths by using Dijkstra's Algo.
*/
int main(int argc, char **argv)
{
    int i;
	srand(time(NULL));
	
	t_tile current_map[96][160];
	roominfo rooms[20];
	int num_mon = default_num_mon;
	
	for (i = 0; i < 20; i++)
		rooms[i].x_start = 0;
        
	if(argc == 3) {
		if((strcmp(argv[1], "--save") == 0 && strcmp(argv[2], "--load") == 0 )|| (strcmp(argv[1], "--load") == 0 && strcmp(argv[2], "--save") == 0)){
			printf("Loading dungeon from file.\n");
			read_load_file(&current_map[0][0], &rooms[0]);
			design_output(&current_map[0][0]);
			write_save_file(&current_map[0][0], &rooms[0]);
			printf("Dungeon re-written to file.\n");
		}
		else if(strcmp(argv[1], "--nummon") == 0){
			num_mon = atoi(argv[2]);
			init_map(&current_map[0][0], &rooms[0]);
		}
		else{
			init_map(&current_map[0][0], &rooms[0]);
		}
	}
	
	else if(argc == 2) {
		if(strcmp(argv[1], "--save") == 0){
			init_map(&current_map[0][0], &rooms[0]);
			design_output(&current_map[0][0]);
			write_save_file(&current_map[0][0], &rooms[0]);
			printf("Dungeon written to file.\n");
		}
		else if(strcmp(argv[1], "--load") == 0){
			printf("Loading dungeon from file.\n");
			read_load_file(&current_map[0][0], &rooms[0]);
			design_output(&current_map[0][0]);
		}
		else{
			init_map(&current_map[0][0], &rooms[0]);
		}
	}
	
	else{
		init_map(&current_map[0][0], &rooms[0]);
	}
       
	i = 0;
	int j = 0;
	int src_rm_no = rand()%12;
	init_display();
	
	queue* monster_queue = init_queue();
	Monster* cur_char;
	
	Player* me = generate_PC();
	
	me -> pos[0] = ((rooms[src_rm_no].x_start)+(rand()%(rooms[src_rm_no].x_dim-2)) + 1);
	me -> pos[1] = ((rooms[src_rm_no].y_start)+(rand()%(rooms[src_rm_no].y_dim-2)) + 1);
	
	current_map[me-> pos[0]][me -> pos[1]].pc = me;
	
	for(j = 0; j < num_mon; j++){
		src_rm_no = rand()%12;
		
		cur_char = generate_monster();
		
		cur_char -> pos[0] = ((rooms[src_rm_no].x_start)+(rand()%(rooms[src_rm_no].x_dim-2)) + 1);
		cur_char -> pos[1] = ((rooms[src_rm_no].y_start)+(rand()%(rooms[src_rm_no].y_dim-2)) + 1);
		
		current_map[cur_char -> pos[0]][cur_char -> pos[1]].mon = cur_char;
	
		queue_add(monster_queue, cur_char, 0);
	}
	
	redraw(current_map, me);
	i=0;
	while(me -> alive != 0 && monster_queue -> queue_size != 0){
		 for(j = 0; j < monster_queue -> queue_size; j++){
			int cur_turn = queue_find_lowest_priority(monster_queue);
			if(me -> priority < cur_turn){
				int add_to_turn = 100/(me -> speed);
				int d_x,d_y,status;
				char ch = getch();
				
				interpret_key(ch, &d_y, &d_x, &status);
				if(status == 6){
					me -> alive = 0;
					break;
				}
				if((status == 1 && current_map[me->pos[0]][me->pos[1]].type == tile_type_upstair) || (status == 2 && current_map[me->pos[0]][me->pos[1]].type == tile_type_downstair)){
					src_rm_no = rand()%12;
					me -> pos[0] = ((rooms[src_rm_no].x_start)+(rand()%(rooms[src_rm_no].x_dim-2)) + 1);
					me -> pos[1] = ((rooms[src_rm_no].y_start)+(rand()%(rooms[src_rm_no].y_dim-2)) + 1);
					
					current_map[me-> pos[0]][me -> pos[1]].pc = me;
					
					for(j = 0; j < num_mon; j++){
						src_rm_no = rand()%12;
						
						cur_char = generate_monster();
						
						cur_char -> pos[0] = ((rooms[src_rm_no].x_start)+(rand()%(rooms[src_rm_no].x_dim-2)) + 1);
						cur_char -> pos[1] = ((rooms[src_rm_no].y_start)+(rand()%(rooms[src_rm_no].y_dim-2)) + 1);
						
						current_map[cur_char -> pos[0]][cur_char -> pos[1]].mon = cur_char;
					
						queue_add(monster_queue, cur_char, 0);
					}
				}
				
				move_character(me, 'p', d_y, d_x, &current_map[0][0]);
				redraw(current_map, me);
				me -> priority += add_to_turn;
			}
			else{
				Monster* cur_char = (Monster*) queue_find_lowest(monster_queue);
				int add_to_turn = 100/(cur_char -> speed);
				if(cur_char -> attribs == 3) {
					free(cur_char -> path_to_player);
					cur_char -> path_to_player = Dijkstra(current_map, me -> pos[0], me -> pos[1], cur_char -> pos[0], cur_char -> pos[1]);
				}
				int* move = monster_movement(cur_char, &current_map[0][0]);
				move_character(cur_char, 'm', *move, *(move+1), &current_map[0][0]);
				free(move);
		 
				queue_add(monster_queue, cur_char, cur_turn + add_to_turn);
			}
		 }
		redraw(current_map, me);
	}
	end_session();
	free(me);
	kill_all_monsters(monster_queue);
	
	return 0;
}

void interpret_key(char ch, int* d_y, int* d_x, int* status){
	if(ch == '7' || ch == 'y') {
		*d_y = -1;
		*d_x = -1;
	}
	else if(ch == '8' || ch == 'k') {
		*d_y = -1;
		*d_x = 0;
	}
	else if(ch == '9' || ch == 'u') {
		*d_y = -1;
		*d_x = 1;
	}
	else if(ch == '6' || ch == 'l') {
		*d_y = 0;
		*d_x = 1;
	}
	else if(ch == '3' || ch == 'n') {
		*d_y = 1;
		*d_x = 1;
	}
	else if(ch == '2' || ch == 'j') {
		*d_y = 1;
		*d_x = 0;
	}
	else if(ch == '1' || ch == 'b') {
		*d_y = 1;
		*d_x = -1;
	}
	else if(ch == '4' || ch == 'n') {
		*d_y = 0;
		*d_x = -1;
	}
	else if(ch == '<') {
		*status = 1;
	}
	else if(ch == '>') {
		*status = 2;
	}
/*
	else if(ch == ' ') {
		*status = 3;
	}
	else if(ch == 'L') {
		*status = 4;
	}
	else if(ch == 'X') {
		*status = 5;
	}
*/
	else if(ch == 'S') {
		*status = 6;
	}
}
