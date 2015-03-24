#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_node {
	int priority;
	void* info;
	struct queue_node *next;
	struct queue_node *prev;
} queue_node;

typedef struct queue {
	struct queue_node* head;
	struct queue_node* tail;
	int queue_size;
} queue;

queue* init_queue();
void kill_queue(queue* q);

void queue_add(queue* q, void* item, int priority);
void queue_decrease(queue* q, void* item, int decrease);
void* queue_find_lowest(queue* q);
int queue_find_lowest_priority(queue *q);

#endif
