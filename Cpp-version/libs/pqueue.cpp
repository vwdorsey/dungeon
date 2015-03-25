#include <cstdlib>
#include "pqueue.hpp"	

	pqueue::pqueue(){
		head = NULL;
		tail = NULL;
		size = 0;
	}
	
	pqueue::~pqueue(){
        if(this != NULL){
            while(size != 0){
                void* item = pull();
            }
        }
	}
	
	void pqueue::push(void* item, int priority){
		queue_node* node = new queue_node();
		node -> info = item;
		node -> priority = priority;
		node->next = NULL;
		node->prev = NULL;
			
		if(size == 0){
			head = tail = node;
			size++;
		}
		else{
			node->prev = tail;
			tail->next = tail = node;
			size++;
		}
	}
	
	void pqueue::decrease(void* item, int decrease){
		queue_node* current = head;
		while(current != NULL){
			if(current -> info == item){
				current -> priority -= decrease;
				if(current -> priority < 0) current -> priority = 0;
			}
			current = current->next;
		}
	}
	
	void* pqueue::pull(){
		int low_priority = lowest_priority();
		if (low_priority == -1) return NULL;
		
		queue_node* current = head;
		while(current != NULL){
			if(current -> priority == low_priority){
				void* ret_info = current -> info;
				if (current -> prev == NULL) head = current -> next;
				else current -> prev -> next = current -> next;

				if (current -> next == NULL) tail = current -> prev;
				else current -> next -> prev = current -> prev;
				
				delete current;
				size--;
				return ret_info;
			}
			else current = current -> next;
		}
		return NULL;
	}
	
	int pqueue::lowest_priority(){
		queue_node* current = head;
		if(current == NULL) return -1;
		
		current = head -> next;
		int low_priority = head -> priority;
		while(current != NULL){
			if(low_priority > current -> priority) low_priority = current -> priority;
			current = current -> next;
		}
		
		return low_priority;
	}
	
