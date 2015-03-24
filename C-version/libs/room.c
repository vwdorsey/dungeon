/*
 * room.c - Contains methods to set Room Information quickly and easily.
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
 
#include "room.h"

/*
	Allows me to quickly set the information for any room in the array. Only used in room generation.
*/
void set_room_info(int x_d, int y_d, int x_s, int y_s, int i, roominfo *r){
	(r + i)->x_dim = x_d;
	(r + i)->y_dim = y_d;
	(r + i)->x_start = x_s;
	(r + i)->y_start = y_s;
}