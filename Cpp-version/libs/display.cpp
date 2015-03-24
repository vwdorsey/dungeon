#include <ncurses.h>
#include "display.hpp"

void display::end_session(){
	endwin();
}

void display::init_display(){
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

void display::redraw(tile layout[columns][rows], Player* pc){
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

