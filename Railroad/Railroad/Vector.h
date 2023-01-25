#ifndef VECTOR_H
#define VECTOR_H

#include "Deque.h"

template <typename T>
class Vector {
private:
	Deque<T> vector;
public:
	//push train onto vector
	void push_back(T& data) {
		vector.push_back(data);
	}
	//return train number at position (index)
	T& at(size_t index) {
		return vector.at(index); 
	}
	//return size of vector
	size_t size(void) const { 
		return vector.size(); 
	}
};

#endif