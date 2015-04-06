#ifndef VALUES_HPP
#define VALUES_HPP

// Monster Attributes Block
#define IS_SMART        1
#define TELEPATHIC      2
#define TUNNEL          4
#define PASS            8
#define BIT4            16
#define BIT5            32
#define BIT6            64
#define BIT7            128
#define BIT8            256
#define BIT9            512
#define BIT10           1024
#define BIT11           2048
#define BIT12           4096
#define BIT13           8192
#define BIT14           16386
#define BIT15           32768

// Object Attributes Block
#define WEAPON       	1
#define OFFHAND     	2
#define RANGED         	4
#define ARMOR           8
#define HELMET          16
#define CLOAK           32
#define GLOVES          64
#define BOOTS           128
#define RING            256
#define AMULET          512
#define LIGHT           1024
#define SCROLL          2048
#define BOOK           	4096
#define FLASK           8192
#define GOLD           	16386
#define AMMUNITION		32768
#define FOOD			65536
#define WAND			131702
#define CONTAINER		262144
//Space left blank for expansions.
#define IS_EQUIPMENT	2147483648

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

// Control Settings
#define num_pad_up '8'
#define num_pad_down '2'
#define num_pad_left '4'
#define num_pad_right '6'
#define num_pad_lfup '7'
#define num_pad_lfdn '1'
#define num_pad_rgup '9'
#define num_pad_rgdn '3'
#define kb_up 'w'
#define kb_down 's'
#define kb_left 'a'
#define kb_right 'd'
#define kb_lfup 'q'
#define kb_lfdn 'z'
#define kb_rgup 'e'
#define kb_rgdn 'x'
#define go_upstairs '<'
#define go_downstairs '>'
#define rest ' '
#define to_look_mode 'L'
#define to_control_mode 27
#define save_and_exit 'S'

//Player Settings
#define pc_sprite '@'
#define pc_speed 10


#endif
