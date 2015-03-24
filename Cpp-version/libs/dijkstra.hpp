#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "pqueue.hpp"
#include "values.hpp"
#include "map.hpp"
#include "structs.hpp"

class dijkstra{
	public:
		point* Dijkstra(tile layout[96][160], int start_y, int start_x, int dest_y, int dest_x);
	private:
		void check_neighbor(pqueue* queue, int dist[columns][rows], dij_node* source, dij_node* dest);
		int check_if_destination(dij_node* d, int d_x, int d_y);
};

#endif
