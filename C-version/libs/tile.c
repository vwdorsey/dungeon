/*
 * tile.c
 * 
 * Copyright 2015 Vaughn Dorsey <vaughn@Vaughn-HP>
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
#include "tile.h"

/*
	This method is a quick way to change the type of a tile, so that I don't have to keep dealing with direct access issues.
*/
void set_type(t_tile *t, int newtype){
	if(newtype == 0){	//Barrier
		t->type = '#';
	}
	
	else if(newtype == 1 && (t->hardness) != 9){ //Empty
		t->type = ' ';
	}
	
	else if(newtype == 2 && (t->hardness) != 9){ //Wall
		t->type = '+';
	}
	
	else if(newtype == 3 && (t->hardness) != 9){ //Floor
		t->type = '.';
	}
}

/*
	This method provides a quick way to determine what a tile currently is. It helps cut down on code related to seeing if the tile is empty.
*/
int get_type(t_tile *t){
	if(t->type == '#'){	//Barrier
		return 0;
	}
	
	else if(t->type == ' '){ //Empty
		return 1;
	}
	
	else if(t->type == '+'){ //Wall
		return 2;
	}
	
	else if(t->type == '.'){ //Floor
		return 3;
	}
	
	else return -1;
}
