#ifndef VALUES_HPP
#define VALUES_HPP

// Character Attributes Block
#define IS_SMART        0x0001
#define TELEPATHIC      0x0002
#define TUNNEL          0x0004 // Unused ingame for now
#define PASS            0x0008 // Unused ingame for now
/* Unnecessary due to lack of attributes.
#define BIT4            0x0010
#define BIT5            0x0020
#define BIT6            0x0040
#define BIT7            0x0080
#define BIT8            0x0100
#define BIT9            0x0200
#define BIT10           0x0400
#define BIT11           0x0800
#define BIT12           0x1000
#define BIT13           0x2000
#define BIT14           0x4000
*/
#define IS_CHARACTER    0x8000

// Object Attributes Block
#define WEAPON       	0x00000001
#define OFFHAND     	0x00000002
#define RANGED         	0x00000004
#define ARMOR           0x00000008
#define HELMET          0x00000010
#define CLOAK           0x00000020
#define GLOVES          0x00000040
#define BOOTS           0x00000080
#define RING            0x00000100
#define AMULET          0x00000200
#define LIGHT           0x00000400
#define SCROLL          0x00000800
#define BOOK           	0x00001000
#define FLASK           0x00002000
#define GOLD           	0x00004000
#define AMMUNITION		0x00008000
#define FOOD			0x00010000
#define WAND			0x00020000
#define CONTAINER		0x00040000
//Space left blank for expansions.
#define IS_EQUIPMENT	0x80000000

// Object Attributes -> Sprites Block
#define SPT_WEAPON       	'|'
#define SPT_OFFHAND     	')'
#define SPT_RANGED         	'}'
#define SPT_ARMOR           '['
#define SPT_HELMET          ']'
#define SPT_CLOAK           '('
#define SPT_GLOVES          '{'
#define SPT_BOOTS           '\\'
#define SPT_RING            '='
#define SPT_AMULET          '"'
#define SPT_LIGHT           '_'
#define SPT_SCROLL          '~'
#define SPT_BOOK           	'?'
#define SPT_FLASK           '!'
#define SPT_GOLD           	'$'
#define SPT_AMMUNITION		'/'
#define SPT_FOOD			','
#define SPT_WAND			'-'
#define SPT_CONTAINER		'%'
#define SPT_NON 			'*'

// Tilings
#define tile_type_wall      '+'
#define tile_type_empty     ' '
#define tile_type_immutable '#'
#define tile_type_floor     '.'
#define tile_type_upstair   '<'
#define tile_type_downstair '>'

// Map Settings
#define rows        160
#define columns     96
#define min_rooms   12
#define max_rooms   20
#define min_room_x  10
#define min_room_y  7
#define max_room_x  20
#define max_room_y  15

// Game Settings
#define default_num_mon 10
#define defs_filename "monster_desc.txt"
#define objs_filename "object_desc.txt"

// Control Settings
#define num_pad_up '8'
#define num_pad_down '2'
#define num_pad_left '4'
#define num_pad_right '6'
#define num_pad_lfup '7'
#define num_pad_lfdn '1'
#define num_pad_rgup '9'
#define num_pad_rgdn '3'
#define kb_up 'u'
#define kb_down 'j'
#define kb_left 'h'
#define kb_right 'k'
#define kb_lfup 'y'
#define kb_lfdn 'n'
#define kb_rgup 'i'
#define kb_rgdn 'm'
#define go_upstairs '<'
#define go_downstairs '>'
#define rest ' '
#define to_look_mode 'L'
#define to_control_mode 27
#define save_and_exit 'S'
#define wear_item 'w'
#define remove_equip 't'
#define drop_item 'd'
#define remove_item 'x'
#define yes 'y'
#define no 'n'

//Player Settings
#define pc_sprite '@'
#define pc_speed 10
#define pc_hitpoints 100

//Ncurses Color Settings
#define BLACK 1
#define RED 2
#define GREEN 3
#define YELLOW 4
#define BLUE 5
#define MAGENTA 6
#define CYAN 7
#define EQUIP 8 //GREEN & WHITE.
#define BACKPACK 9 //BLUE & WHITE.
#define DIALOG 10 //YELLOW & BLACK.

#endif
