#ifndef STATION_H
#define STATION_H

#include "sstream"
#include "string"
#include "Queue.h"
#include "Stack.h"
#include "Vector.h"
using namespace std;

template <typename T>
class Station {
private:
	Vector<T> vector;
	Stack<T> stack;
	Queue<T> queue;
	T turntable;
public:
	Station() : turntable(0) {}
	
	//put incoming train on turntable
	bool setTurntable(unsigned int train) {
		if (turntable == 0) {
			turntable = train;
			return true;
		}
		else return false; //turntable occupied
	}

	//move train from turntable to queue
	bool addQueue() {
		if (turntable != 0) {
			queue.push(turntable);
			turntable = 0;
			return true;
		}
		else return false; //turntable empty
	}

	//move train from turntable to stack
	bool addStack() {
		if (turntable != 0) {
			stack.push(turntable);
			turntable = 0;
			return true;
		}
		else return false; //turntable empty
	}
	
	//move train from turntable to outgoing vector
	bool removeStation() {
		if (turntable != 0) {
			vector.push_back(turntable);
			turntable = 0;
			return true;
		}
		else return false; //turntable empty
	}

	//move train from queue to turntable
	int removeQueue() {
		if (queue.size() == 0) return 0; //queue is empty
		else if (turntable != 0) return 1; //turntable is occupied
		else {
			turntable = queue.front();
			queue.pop();
			return 2; //success
		}
	}

	//move train from stack to turntable
	int removeStack() {
		if (stack.size() == 0) return 0; //stack is empty
		else if (turntable != 0) return 1; //turntable is occupied
		else {
			turntable = stack.back();
			stack.pop();
			return 2; //success
		}
	}

	//return number of the train on turntable
	unsigned int getTurntable() { return turntable; } //if turntable is 0, it is empty

	//return number of the train that is the next one out of the queue
	unsigned int topQueue() {
		if (queue.size() == 0) {
			return -1; //queue is empty
		}
		else return queue.front();
	}

	//return number of the train that is on the top of the stack
	unsigned int topStack() {
		if (stack.size() == 0) {
			return -1; //stack is empty
		}
		else return stack.back();
	}

	//return number of trains in the queue
	unsigned int sizeQueue() {
		return queue.size();
	}

	//return number of trains in the stack
	unsigned int sizeStack() {
		return stack.size();
	}

	//return cars of the outgoing train
	string trainContents() {
		ostringstream oss;
		for (size_t i = 0; i < vector.size(); i++) {
			oss << " " << vector.at(i);
		}
		return oss.str();
	}
};

#endif