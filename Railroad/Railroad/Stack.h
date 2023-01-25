#ifndef STACK_H
#define STACK_H

#include "Deque.h"

template <typename T>
class Stack {
private:
	Deque<T> stack;
public:
	//push train onto stack
	void push(T& data) {
		stack.push_back(data);
	}
	//remove train from top of stack
	void pop(void) {
		stack.pop_back();
	}
	//return value of train on top of stack
	T& back(void) {
		return stack.back();
	}
	//return size of stack
	size_t size(void) const { 
		return stack.size(); 
	}
};

#endif