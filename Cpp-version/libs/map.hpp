#ifndef MAP_H
#define MAP_H

#include <random>
#include "structs.hpp"
#include "values.hpp"

class map{
	public:
		map();
		~map();
		
		tile layout[columns][rows];
		room room_info[20];
		int room_count;
		
		void init_map();
		void design_output();
        
	private:
		void place_rooms();
		char check_room_placement(int y_dim, int x_dim, int y, int x);
		void determine_paths();
		void generate_corridors(int s_y, int s_x, int src_pnl, int d_y, int d_x);
		std::default_random_engine random;
		std::uniform_int_distribution<int> column_dist;
		std::uniform_int_distribution<int> row_dist;
};

#endif
