#ifndef PQUEUE_HPP
#define PQUEUE_HPP

class pqueue{
	public:
		pqueue();
		~pqueue();
		
		void push(void* item, int priority);
		void decrease(void* item, int decrease);
		void* pull();
		int lowest_priority();
		int get_size(){ return size; };
	private:
		struct queue_node {
			int priority;
			void* info;
			struct queue_node *next;
			struct queue_node *prev;
		};
		
		queue_node* head;
		queue_node* tail;
		int size;
};

#endif
