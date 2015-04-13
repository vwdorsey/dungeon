#include <iostream>
#include "dijkstra.hpp"

using namespace std; 
	
	point* dijkstra::Dijkstra(tile layout[columns][rows], int start_y, int start_x, int dest_y, int dest_x){
		pqueue* queue = new pqueue();
		int dist[columns][rows];
		dij_node* nodes[columns][rows];
		
		for(int y = 0; y < columns; y++){
			for(int x = 0; x < rows; x++){
				if(layout[y][x].type == tile_type_floor){
					dij_node* dn = new dij_node();
					dist[y][x] = 1000000;
					dn -> x = x;
					dn -> y = y;
					dn -> previous = 0;
					if(y == start_y && x == start_x){
						dist[y][x] = 0;
					}
					queue -> push(dn, dist[y][x]);
					nodes[y][x] = dn;
				}
				else nodes[y][x] = NULL;
			}
		}
		
		while(queue -> get_size() != 0){
			dij_node* d = (dij_node*) queue -> pull();
			
			int x = d -> x;
			int y = d -> y;
			
			if(layout[y][x+1].type == tile_type_floor) {
                check_neighbor(queue, dist, d, nodes[y][x+1]);
            }
            if(layout[y+1][x].type == tile_type_floor) {
                check_neighbor(queue, dist, d, nodes[y+1][x]);
            }
            if(layout[y][x-1].type == tile_type_floor) {
                check_neighbor(queue, dist, d, nodes[y][x-1]);
            }
            if(layout[y-1][x].type == tile_type_floor) {
                check_neighbor(queue, dist, d, nodes[y-1][x]);
            }
            if(layout[y+1][x+1].type == tile_type_floor) {
                check_neighbor(queue, dist, d, nodes[y+1][x+1]);
            }
            if(layout[y-1][x+1].type == tile_type_floor) {
                check_neighbor(queue, dist, d, nodes[y-1][x+1]);
            }
            if(layout[y+1][x-1].type == tile_type_floor) {
                check_neighbor(queue, dist, d, nodes[y+1][x-1]);
            }
            if(layout[y-1][x-1].type == tile_type_floor) {
                check_neighbor(queue, dist, d, nodes[y-1][x-1]);
            }
		}
		
		delete queue;
		int array_size = 0;
		
		if (nodes[dest_y][dest_x]->previous != NULL) {
			dij_node *src = nodes[start_y][start_x], *current = nodes[dest_y][dest_x];
			while (current != src) {
				if (current == NULL)
					exit(3);
				else if (current->x >= 160 || current->y >= 96) {
				   //std::cout << current->x << " , " << current->y;
				   std::cout << ("Bad path \n");
				   array_size = 0;
				   return NULL;
				}
				array_size++;
				current = current->previous;

			}
		} 
    else {
        std::cout << ("No path found!\n");
        array_size = 0;
    } 
    
    point* path_array = new point[array_size+2]();
    
    if(array_size != 0){
        
        dij_node *current = nodes[dest_y][dest_x];
        
        for(int i = array_size; i > 0 ; i--){
          path_array[i].n_x = current -> x;
          path_array[i].n_y = current -> y;
          path_array[i].path_size = array_size;
          current = current->previous;
        }
    }
    else path_array = NULL;
		
		for(int y = 0; y < columns; y++){
			for(int x = 0; x < rows; x++){
				if(nodes[y][x] != NULL){
					dij_node* temp = nodes[y][x];
					delete temp;
				}
			}
		}
		
	return path_array;
	}
	
	void dijkstra::check_neighbor(pqueue* queue, int dist[columns][rows], dij_node* source, dij_node* dest){
		if (dest == NULL || source == NULL) return;

		unsigned int alt = dist[source -> y][source -> x] + 1;
		
		if (alt < dist[dest -> y][dest -> x]){
				dist[dest -> y][dest -> x] = alt;
				dest -> previous = source;
				queue -> decrease(dest, 1000000-alt);
		}
	}
	
	int dijkstra::check_if_destination(dij_node* d, int d_x, int d_y){
		return (d -> x == d_x && d -> y == d_y);
	}
