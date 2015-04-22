#include <ncurses.h>
#include "display.hpp"
#include <iostream>

void display::end_session(){
	endwin();
}

void display::init_display(){
	initscr();
	//keypad(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();

	start_color();
	init_pair(BLACK, COLOR_WHITE, COLOR_BLACK);
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
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

void display::redraw_with_templates(tile layout[columns][rows], Player* me){
	draw_container active_disp[24][80];
	int i,j;
	int x_center = me -> pos[1];
	int y_center = me -> pos[0];

	for(i = 0; i < 24; i++){
		for(j = 0; j < 80; j++){
			if((y_center - 12 + i) < 0 || (x_center - 40 + j) < 0 || (y_center - 12 + i) >= columns || (x_center - 40 + j) >= rows) {
					active_disp[i][j].sprite = '#';
					active_disp[i][j].color = 0;
					}
			else {
				if(layout[(y_center-12) + i][(x_center - 40) + j].pc) {
					active_disp[i][j].sprite = layout[(y_center-12) + i][(x_center - 40) + j].pc->Sprite;
					active_disp[i][j].color = 0;
				}
				else if(layout[(y_center-12) + i][(x_center - 40) + j].mon){
					if(layout[(y_center-12) + i][(x_center - 40) + j].mon->alive){
						active_disp[i][j].sprite = layout[(y_center-12) + i][(x_center - 40) + j].mon->Sprite;
						active_disp[i][j].color = layout[(y_center-12) + i][(x_center - 40) + j].mon->ch->Color;
					}
					else {
						active_disp[i][j].sprite = layout[(y_center-12) + i][(x_center - 40) + j].type;
						active_disp[i][j].color = 0;
					}
				}
				else if(layout[(y_center-12) + i][(x_center - 40) + j].obj){
					active_disp[i][j].sprite = layout[(y_center-12) + i][(x_center - 40) + j].obj->Sprite;
					active_disp[i][j].color = layout[(y_center-12) + i][(x_center - 40) + j].obj->Color;
				}
				else {
					active_disp[i][j].sprite = layout[(y_center-12) + i][(x_center - 40) + j].type;
					active_disp[i][j].color = 0;
				}
			}
		}
	}

	for(i = 0; i<24; i++){
		for(j=0; j<80; j++){
			draw_color(i,j,active_disp[i][j]);
		}
	}

	refresh();
}

void display::draw_color(int i, int j, draw_container draw){
	if(draw.color) attron(COLOR_PAIR(draw.color));
	mvaddch(i,j,draw.sprite);
	if(draw.color) attroff(COLOR_PAIR(draw.color));
}