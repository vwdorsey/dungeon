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
	init_pair(EQUIP, COLOR_WHITE, COLOR_GREEN);
	init_pair(BACKPACK, COLOR_WHITE, COLOR_BLUE);
	init_pair(DIALOG, COLOR_BLACK, COLOR_YELLOW);
}
/*
void display::redraw(tile layout[columns][rows], PC* me){
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
*/
void display::redraw_with_templates(tile layout[columns][rows], PC* me){
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
						active_disp[i][j].color = layout[(y_center-12) + i][(x_center - 40) + j].mon->Color;
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

void display::draw_equip_menu(PC* me, int mode){
	int i_x = 5;
	int i_y = 2;
	std::string text;
	if(mode == 1) text = "Select the piece of equipment you'd like to remove - ESC to cancel";
	else text = "Your Equipped Items - ESC to close";

	for(int i=0; i < 16; i++){
		for(int j=0; j < 70; j++){
			if(i==0 || i==15 || j==0 || j==69){
				active_disp[i_y+i][i_x+j].sprite = '+';
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==1 &&(j>2 && j<text.size()+2)){
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==3 &&(j>2 && j<text.size()+2)){ //WEAPON
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==4 &&(j>2 && j<text.size()+2)){ //OFFHAND
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==5 &&(j>2 && j<text.size()+2)){ //RANGED
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==6 &&(j>2 && j<text.size()+2)){ //ARMOR
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==7 &&(j>2 && j<text.size()+2)){ //HELMET
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==7 &&(j>2 && j<text.size()+2)){ //CLOAK
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==7 &&(j>2 && j<text.size()+2)){ //GLOVES
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==7 &&(j>2 && j<text.size()+2)){ //BOOTS
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==7 &&(j>2 && j<text.size()+2)){ //AMULET
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==7 &&(j>2 && j<text.size()+2)){ //LIGHT
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==7 &&(j>2 && j<text.size()+2)){ //RING
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else if(i==7 &&(j>2 && j<text.size()+2)){ //RING
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
			else{
				active_disp[i_y+i][i_x+j].sprite = ' ';
				active_disp[i_y+i][i_x+j].color = EQUIP;
			}
		}
	}

	for(int i = 0; i<24; i++){
		for(int j=0; j<80; j++){
			draw_color(i,j,active_disp[i][j]);
		}
	}

	refresh();
}

void display::draw_backpack_menu(PC* me, int mode){
	int i_x = 5;
	int i_y = 3;
	std::string text;
	if(mode == 1){
		text = "Select an item that you'd like to equip - ESC to cancel";
	}
	else if(mode == 2){
		text = "Select an item to toss on the floor - ESC to cancel";
	}
	else if(mode == 3){
		text = "Select an item to remove from the game - ESC to cancel";
	}
	else{
		text = "Your Backpack - ESC to close";
	}
	int item_no = 1;
	for(int i=0; i < 14; i++){
		for(int j=0; j < 70; j++){
			if(i==0 || i==13 || j==0 || j==69){
				active_disp[i_y+i][i_x+j].sprite = '+';
				active_disp[i_y+i][i_x+j].color = BACKPACK;
			}
			else if(i==1 &&(j>2 && j<text.size()+3)){
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = BACKPACK;
			}
			else if(i>2 &&j==1){
				active_disp[i_y+i][i_x+j].sprite = 47+item_no;
				active_disp[i_y+i][i_x+j].color = BACKPACK;
			}
			else if(i>2 && (j>2 && j<text.size()+3)){
				if(i-3 < me->backpack.size()){
					text = me->backpack[item_no-1]->print_obj();
					active_disp[i_y+i][i_x+j].sprite = text[j-3];
					active_disp[i_y+i][i_x+j].color = BACKPACK;
				}
				else {
					active_disp[i_y+i][i_x+j].sprite = ' ';
					active_disp[i_y+i][i_x+j].color = BACKPACK;
				}
			}
			else{
				active_disp[i_y+i][i_x+j].sprite = ' ';
				active_disp[i_y+i][i_x+j].color = BACKPACK;
			}

		}
		if(i>2) {
			item_no++;
		}
	}

	for(int i = 0; i<24; i++){
		for(int j=0; j<80; j++){
			draw_color(i,j,active_disp[i][j]);
		}
	}

	refresh();
}

void display::AYS_prompt(){
	int i_x = 23;
	int i_y = 11;
	char text[] = "Are you sure? (Press y/n)";

	for(int i=0; i < 3; i++){
		for(int j=0; j < 31; j++){
			if(i==0 || i==2 || j==0 || j==30){
				active_disp[i_y+i][i_x+j].sprite = '+';
				active_disp[i_y+i][i_x+j].color = DIALOG;
			}
			else if(i==1 &&(j>2 && j<28)){
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = DIALOG;
			}
			else{
				active_disp[i_y+i][i_x+j].sprite = ' ';
				active_disp[i_y+i][i_x+j].color = DIALOG;
			}
		}
	}

	for(int i = 0; i<24; i++){
		for(int j=0; j<80; j++){
			draw_color(i,j,active_disp[i][j]);
		}
	}

	refresh();
}

void display::prompt(std::string text){
	int i_x = 5;
	int i_y = 11;

	for(int i=0; i < 3; i++){
		for(int j=0; j < 70; j++){
			if(i==0 || i==2 || j==0 || j==69){
				active_disp[i_y+i][i_x+j].sprite = '+';
				active_disp[i_y+i][i_x+j].color = DIALOG;
			}
			else if(i==1 &&(j>2 && j<text.size()+3)){
				active_disp[i_y+i][i_x+j].sprite = text[j-3];
				active_disp[i_y+i][i_x+j].color = DIALOG;
			}
			else{
				active_disp[i_y+i][i_x+j].sprite = ' ';
				active_disp[i_y+i][i_x+j].color = DIALOG;
			}
		}
	}

	for(int i = 0; i<24; i++){
		for(int j=0; j<80; j++){
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
