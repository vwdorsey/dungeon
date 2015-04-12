#include <ncurses.h>
#include "display.hpp"


void display::end_session(){
	endwin();
}

void display::init_display(){
	initscr();
	//keypad(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();
}

void display::redraw(tile layout[columns][rows], Player* me){
	char active_disp[24][80];
	int i,j;
	int x_center = me -> pos[1];
	int y_center = me -> pos[0];
	for(i = 0; i<24; i++){
		for(j=0; j<80; j++){
			if((y_center - 12 + i) < 0 || (x_center - 40 + j) < 0 || (y_center - 12 + i) >= columns || (x_center - 40 + j) >= rows) active_disp[i][j] = '#';
			else{
				if(layout[(y_center-12) + i][(x_center - 40) + j].pc) active_disp[i][j] = layout[(y_center-12) + i][(x_center - 40) + j].pc -> Sprite;
				else if(layout[(y_center-12) + i][(x_center - 40) + j].mon){
					if(layout[(y_center-12) + i][(x_center - 40) + j].mon->alive) active_disp[i][j] = layout[(y_center-12) + i][(x_center - 40) + j].mon -> Sprite;
					else active_disp[i][j] = layout[(y_center-12) + i][(x_center - 40) + j].type;
				}
				else active_disp[i][j] = layout[(y_center-12) + i][(x_center - 40) + j].type;
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

