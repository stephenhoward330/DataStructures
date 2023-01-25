#ifndef MYARRAY_H
#define MYARRAY_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#define MAX_ARRAY_SIZE 1000

using namespace std;

template<typename T>
class MyArray {
private:
	size_t size_;
	T* array_;
public:
	MyArray(size_t maxSize) : size_(0) {
		array_ = (T*)malloc(maxSize * sizeof(T));
	}
	~MyArray() {
		free(array_);
	}
	void push_back(T item) { array_[size_++] = item; }
	string toString() const {
		stringstream out;
		out << "myArray:";
		for (size_t i = 0; i < size_; ++i)
			out << ((i % 10) ? " " : "\n") << array_[i];
		return out.str();
	}
	friend ostream& operator<< (ostream& os, const MyArray<T>& myArray) {
		os << myArray.toString();
		return os;
	}
	class Iterator {
	private:
		size_t index_;
		T* array_;
	public:
		Iterator(T* a, size_t s) : array_(a), index_(s) {
			array_[index_];
		}
		size_t getIndex() { return index_; }
		T& operator[](size_t i) const { return array_[index_]; }
		T& operator*() const { return array_[index_]; }
		T& operator++() { 
			index_ += 1;
			return array_[index_];
		}
		bool operator!=(Iterator b) {
			if (this->getIndex() == b.getIndex()) return false;
			return true;
		}
		string toString() const {
			stringstream out;
			out << array_[index_];
			return out.str();
		}
		friend ostream& operator<< (ostream& os, const Iterator& iter) {
			os << iter.toString();
			return os;
		}
	};
	Iterator begin() { return MyArray<T>::Iterator(array_, 0); }
	Iterator end() { return MyArray<T>::Iterator(array_, size_); }
	size_t getSize() { return size_; }
};

#endif