/*
	path.c : Dijkstra's Algorithm for Pathfinding
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "tile.h"
#include "path.h"
#include "generation.h"

typedef struct tile t_tile;

void check_neighbor(queue* q, int dist[96][160], dij_node* source, dij_node* dest);
int check_if_destination(dij_node* d, int d_x, int d_y);

point* Dijkstra(t_tile map[96][160], int s_y, int s_x, int d_y, int d_x){
	int i = 0;
	int j = 0;
	
	queue *q = init_queue();
	int distance[96][160];
	dij_node* nodes[96][160];
        
   // Initialization
    for(i = 0; i < 96; i++){  
		for(j = 0; j < 160; j++){
			if (get_type(&map[i][j]) == 3){
			dij_node* dn = malloc(sizeof(dij_node));
 			distance[i][j] = 1000000;
			dn -> x = j;
			dn -> y = i;
                        dn -> previous = 0;
			if (j == s_x && i == s_y){
				distance[i][j] = 0;
			}
			queue_add(q, dn, distance[i][j]);
			nodes[i][j] = dn;
                    } else 
                        nodes[i][j] = NULL;
		}
    }
    
    while(q -> queue_size != 0){               // The main loop
        dij_node* d = (dij_node*) queue_find_lowest(q); // Remove and return best vertex
            
            int x = d->y;
            int y = d->x;
            
            if(map[x][y+1].type == tile_type_floor) {
                check_neighbor(q, distance, d, nodes[x][y+1]);
            }
            if(map[x+1][y].type == tile_type_floor) {
                check_neighbor(q, distance, d, nodes[x+1][y]);
            }
            if(map[x][y-1].type == tile_type_floor) {
                check_neighbor(q, distance, d, nodes[x][y-1]);
            }
            if(map[x-1][y].type == tile_type_floor) {
                check_neighbor(q, distance, d, nodes[x-1][y]);
            }
            if(map[x+1][y+1].type == tile_type_floor) {
                check_neighbor(q, distance, d, nodes[x+1][y+1]);
            }
            if(map[x-1][y+1].type == tile_type_floor) {
                check_neighbor(q, distance, d, nodes[x-1][y+1]);
            }
            if(map[x+1][y-1].type == tile_type_floor) {
                check_neighbor(q, distance, d, nodes[x+1][y-1]);
            }
            if(map[x-1][y-1].type == tile_type_floor) {
                check_neighbor(q, distance, d, nodes[x-1][y-1]);
            }
    }
    
    kill_queue(q);
    
    int array_size = 0;
    
    if (nodes[d_y][d_x]->previous != NULL) {
        dij_node *src = nodes[s_y][s_x], *current = nodes[d_y][d_x];
        while (current != src) {
            if (current == NULL)
                exit(3);
            else if (current->x >= 160 || current->y >= 96) {
               printf("Bad path :( \n");
               array_size = 0;
               return NULL;
			}
			array_size++;
            current = current->previous;
        }
    } 
    else {
        printf("No path found!\n");
        array_size = 0;
    } 
    
    point* path_array;
    
    if(array_size != 0){
        
        dij_node *current = nodes[d_y][d_x];
        path_array = malloc(sizeof(point) * (array_size+5));
        
        for(i = 0; i < array_size; i++){
          path_array[i].n_x = current -> x;
          path_array[i].n_y = current -> y;
          path_array[i].path_size = array_size;
          current = current->previous;
        }
    }
    else path_array = NULL;
    
    for(i = 0; i < 96; i++){  
        for(j = 0; j < 160; j++){
            if (nodes[i][j] != NULL)
                free(nodes[i][j]);
        }
    }
    
    return path_array;
}

void check_neighbor(queue* q, int dist[96][160], dij_node* source, dij_node* dest){
        if (dest == NULL || source == NULL)
            exit(1);
    
	unsigned int alt = dist[source -> y][source -> x] + 1;
	
	if (alt < dist[dest -> y][dest -> x]){
            dist[dest -> y][dest -> x] = alt;
            dest -> previous = source;
            queue_decrease(q, dest, 1000000-alt);
	}
	
}

int check_if_destination(dij_node* d, int d_x, int d_y){
        return (d -> x == d_x && d -> y == d_y);
}
