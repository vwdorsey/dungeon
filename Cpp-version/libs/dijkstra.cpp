#include <iostream>
#include "dijkstra.hpp"

using namespace std;
	
	point* dijkstra::Dijkstra(tile layout[96][160], int start_y, int start_x, int dest_y, int dest_x){
		pqueue* queue = new pqueue();
		int dist[columns][rows];
		dij_node* nodes[columns][rows];
		
		for(int y = 0; y < columns; y++){
			for(int x = 0; x < rows; x++){
				dij_node* dn = new dij_node;
				dist[y][x] = 100000;
				dn -> x = x;
				dn -> y = y;
				dn -> previous = 0;
				if(y == start_y && x == start_x){
					dist[y][x] = 0;
				}
				queue -> push(dn, dist[y][x]);
				nodes[y][x] = dn;
			}
		}
		
		delete queue;
		
		for(int y = 0; y < columns; y++){
			for(int x = 0; x < rows; x++){
				dij_node* temp = nodes[y][x];
				delete temp;
			}
		}
	}
	
	void dijkstra::check_neighbor(pqueue* queue, int dist[columns][rows], dij_node* source, dij_node* dest){
		
	}
	
	int dijkstra::check_if_destination(dij_node* d, int d_x, int d_y){
		
	}
