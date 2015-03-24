/*
 * display.c
 * 
 * Copyright 2015 Vaughn <vaughn@vaughn-virtual-machine>
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
#include <ncurses.h>
#include <signal.h>
#include "defs.h"
#include "queue.h"

void end_session(){
	endwin();
}

void init_display(){
	(void) signal(SIGINT, end_session);
	(void) signal(SIGSEGV, end_session);
	
	initscr();
	keypad(stdscr, TRUE);
	nonl();
	cbreak();
	echo();
	
	if(has_colors()){
		start_color();
		
		init_pair(1, COLOR_RED, COLOR_BLACK);
	}

}

void redraw(t_tile map[96][160], Player* me){
	char active_disp[24][80];
	int i,j;
	int x_center = me -> pos[1];
	int y_center = me -> pos[0];
	for(i = 0; i<24; i++){
		for(j=0; j<80; j++){
			if((y_center - 12 + i) < 0 || (x_center - 40 + j) < 0) active_disp[i][j] = '#';
			else{
				if(map[(y_center-12) + i][(x_center - 40) + j].pc) active_disp[i][j] = map[(y_center-12) + i][(x_center - 40) + j].pc -> Sprite;
				else if(map[(y_center-12) + i][(x_center - 40) + j].mon) active_disp[i][j] = map[(y_center-12) + i][(x_center - 40) + j].mon -> Sprite;
				else active_disp[i][j] = map[(y_center-12) + i][(x_center - 40) + j].type;
			}
		}
	}
	
	for(i = 0; i<24; i++){
		for(j=0; j<80; j++){
			mvaddch(i,j,active_disp[i][j]);
		}
	}
	
	refresh();
}
