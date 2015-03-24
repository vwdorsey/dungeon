/*
	queue.c - An inefficient queue implementation based on Linkedlists
*/

#include <stdlib.h>
#include "queue.h"

queue* init_queue(){
	queue* new = (queue*) malloc(sizeof(queue));
	new -> queue_size = 0;
	new -> head = NULL;
	new -> tail = NULL;
	return new;
}

void kill_queue(queue *q){
        if(q -> queue_size != 0){
            queue_node* current = q -> head;
            while(current != NULL){
                    queue_node* to_free = current -> next;
                    free(current);
                    current = to_free;
            }
        }
	free(q);
}

void queue_add(queue *q, void *item, int priority){
	queue_node* new = (queue_node*) malloc(sizeof(queue_node));
	new -> info = item;
	new -> priority = priority;
	
        new->next = NULL;
        new->prev = NULL;
        
	if(q -> queue_size == 0){
		q -> head = q -> tail = new;
		q -> queue_size++;
	}
	else{
		queue_node* current_last = q -> tail;
		new->prev = current_last;
		current_last->next = q -> tail = new;
		q -> queue_size++;
	}
	
}

void queue_decrease(queue *q, void *item, int decrease){
	queue_node* current = q -> head;
	while(current != NULL){
		if(current -> info == item){
			current -> priority -= decrease;
			if(current -> priority < 0) current -> priority = 0;
		}
		current = current->next;
	}
}

void* queue_find_lowest(queue *q){
	queue_node* current = q -> head;
	if(current == NULL) return NULL;
	
	current = q -> head -> next;
	int low_priority = q -> head -> priority;
	while(current != NULL){
		if(low_priority > current -> priority) low_priority = current -> priority;
		current = current -> next;
	}
	
	current = q -> head;
	while(current != NULL){
		if(current -> priority == low_priority){
			void* ret_info = current -> info;
			if (current -> prev == NULL) q -> head = current -> next;
			else current -> prev -> next = current -> next;

			if (current -> next == NULL) q -> tail = current -> prev;
			else current -> next -> prev = current -> prev;
			
			free(current);
			q -> queue_size--;
			return ret_info;
		}
		else current = current -> next;
	}
	return NULL;
}

int queue_find_lowest_priority(queue *q){
        queue_node* current = q -> head;
	if(current == NULL) return -1;
	
	current = q -> head -> next;
	int low_priority = q -> head -> priority;
	while(current != NULL){
		if(low_priority > current -> priority) low_priority = current -> priority;
		current = current -> next;
	}
	
	return low_priority;
}

