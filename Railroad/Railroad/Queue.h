#ifndef QUEUE_H
#define QUEUE_H

#include "Deque.h"

template <typename T>
class Queue {
private:
	Deque<T> queue;
public:
	//push train onto back of queue
	void push(T& data) {
		queue.push_back(data);
	}
	//remove train from front of queue
	void pop(void) {
		queue.pop_front();
	}
	//return value of train at the front of queue
	T& front(void) {
		return queue.front();
	}
	//return size of queue
	size_t size(void) const { 
		return queue.size(); 
	}
};

#endif