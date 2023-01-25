#ifndef DEQUE_H
#define DEQUE_H

#include "DequeInterface.h"
#include <string>

#define DEFAULT_CAPACITY 4

using std::string;

template<typename T>
class Deque : public DequeInterface<T> {
private:
	size_t capacity;
	size_t numItems;
	size_t frontIndex;
	size_t rearIndex;
	T* theData;

	// doubles capacity of the deque
	void reallocate() {
		size_t newCapacity = 2 * capacity;
		T* newData = new T[newCapacity];
		size_t j = frontIndex;
		for (size_t i = 0; i < numItems; i++) {
			newData[i] = theData[j];
			j = (j + 1) % capacity;
		}
		frontIndex = 0;
		rearIndex = numItems - 1;
		capacity = newCapacity;
		std::swap(theData, newData);
		delete[] newData;
	}
public:
	Deque(void) {
		capacity = DEFAULT_CAPACITY;
		numItems = 0;
		frontIndex = 0;
		rearIndex = DEFAULT_CAPACITY - 1;
		theData = new T[capacity];
	}
	~Deque(void) {
		delete[] theData;
	}

	/** Insert item at front of deque */
	virtual void push_front(const T& value) {
		if (numItems == capacity) {
			reallocate();
		}
		numItems++;
		frontIndex = frontIndex - 1;
		if (frontIndex < 0) frontIndex = capacity - 1;
		//frontIndex = (frontIndex - 1) % capacity;
		theData[frontIndex] = value;
	}

	/** Insert item at rear of deque */
	virtual void push_back(const T& value) {
		if (numItems == capacity) {
			reallocate();
		}
		numItems++;
		rearIndex = (rearIndex + 1) % capacity;
		theData[rearIndex] = value;
		return;
	}

	/** Remove the front item of the deque */
	virtual void pop_front(void) {
		theData[frontIndex] = 0;
		numItems--;
		frontIndex = (frontIndex + 1) % capacity;
	}

	/** Remove the rear item of the deque */
	virtual void pop_back(void) { 
		theData[rearIndex] = 0;
		numItems--;
		rearIndex = rearIndex - 1;
		if (rearIndex < 0) rearIndex = capacity - 1;
	}

	/** Return the front item of the deque (Do not remove) */
	virtual T& front(void) { return theData[frontIndex]; }

	/** Return the rear item of the deque (Do not remove) */
	virtual T& back(void) { return theData[rearIndex]; }

	/** Return the number of items in the deque */
	virtual size_t size(void) const { return numItems; }

	/** Return true if deque is empty */
	virtual bool empty(void) const {
		if (numItems == 0) return true;
		else return false;
	}

	/** Return item in deque at index (0 based) */
	virtual T& at(size_t index) { 
		//T* original = theData[(index + frontIndex) % capacity];
		//T& fin = original;
		//return fin;
		
		return theData[(index + frontIndex) % capacity];
	}

	/** Return the deque items */
	virtual string toString() const { return "NOT IMPLEMENTED"; }
};
#endif