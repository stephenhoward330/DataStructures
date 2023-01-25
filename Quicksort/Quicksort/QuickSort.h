#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "QSInterface.h"
#include <sstream>
using namespace std;

template<typename T>
class QuickSort: public QSInterface<T> {
private:
	T* data;
	size_t arraySize;
	size_t arrayCapacity;

	/** Doubles capacity of the array */
	void resize() {
		size_t newCapacity = 2 * arrayCapacity;
		T* newData = new T[newCapacity];
		for (size_t i = 0; i < arraySize; i++) {
			newData[i] = data[i];
		}
		arrayCapacity = newCapacity;
		swap(data, newData);
		delete[] newData;
	}
public:
	QuickSort() {
		arraySize = 0;
		arrayCapacity = 0;
	}
	virtual ~QuickSort() { delete[] data; }

	/** Dynamically allocate an initial array to the QuickSort class. */
	virtual bool createArray(size_t capacity) {
		if (arrayCapacity > 0) delete[] data;
		data = new T[capacity];
		arraySize = 0;
		arrayCapacity = capacity;
		return true;
	}

	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	virtual bool addElement(T element) {
		if (arrayCapacity == arraySize) resize();
		data[arraySize] = element;
		arraySize++;
		return true;
	}

	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	virtual bool sort(size_t left, size_t right) {
		if (right - left <= 1) return true;
		int middle = medianOfThree(left, right);
		int location = partition(left, right, middle);
		sort(left, location);
		sort(location+1, right);
	}

	/** Sort all elements of the QuickSort array using median and partition functions. */
	virtual bool sortAll() {
		return sort(0, arraySize);
	}

	/** Removes all items from the QuickSort array. */
	virtual bool clear() {
		for (size_t i = 0; i < arraySize; i++) {
			data[i] = NULL;
		}
		arraySize = 0;
		return true;
	}

	/** Return size of the QuickSort array. */
	virtual size_t capacity() const { return arrayCapacity; }

	/** Return number of elements in the QuickSort array. */
	virtual size_t size() const { return arraySize; }

	/** The median of three pivot selection has two parts:
	1) Calculates the middle index by averaging the given left and right indices:
	middle = (left + right)/2
	2) Then bubble-sorts the values at the left, middle, and right indices.

	After this method is called, data[left] <= data[middle] <= data[right].

	@param left - the left boundary for the subarray from which to find a pivot
	@param right - the right + 1 boundary for the subarray from which to find a pivot
	@return the index of the pivot (middle index).
	Return -1 if	1) the array is empty,
	2) if either of the given integers is out of bounds,
	3) or if the left index is not less than the right index.
	*/
	virtual int medianOfThree(size_t left, size_t right) {
		if (arraySize == 0 || left < 0 || (right - 1) >= arraySize || left >= right) return -1;
		int middle = (left + right) / 2;
		if (data[left] > data[middle]) swap(data[left], data[middle]);
		if (data[middle] > data[right-1]) swap(data[middle], data[right-1]);
		if (data[left] > data[middle]) swap(data[left], data[middle]);
		return middle;
	}

	/** Partitions a subarray around a pivot value selected according
	to median-of-three pivot selection. Because there are multiple ways
	to partition a list, follow the algorithm on page 611.

	The values which are smaller than the pivot should be placed to the left of the pivot;
	the values which are larger than the pivot should be placed to the right of the pivot.

	@param left - left index for the subarray to partition.
	@param right - right index + 1 for the subarray to partition.
	@param pivotIndex - index of the pivot in the subarray.
	@return the pivot's ending index after the partition completes:
	Return -1 if	1) the array is empty,
	2) if any of the given indexes are out of bounds,
	3) if the left index is not less than the right index.
	*/
	virtual int partition(size_t left, size_t right, size_t pivotIndex) {
		if (arraySize == 0 || left < 0 || pivotIndex < left || pivotIndex >= right
			|| (right - 1) >= arraySize || left >= right) return -1;
		swap(data[left], data[pivotIndex]);
		size_t up = left + 1;
		size_t down = right - 1;
		while (up < down) {
			while ((up != right - 1) && !(data[left] < data[up])) ++up;
			while (data[left] < data[down]) --down;
			if (up < down) swap(data[up], data[down]);
		}
		swap(data[left], data[down]);
		return down;
	}

	/** @return: comma delimited string representation of the array. */
	virtual std::string toString() const {
		ostringstream oss;
		if (arraySize == 0) oss << "Empty";
		else {
			for (size_t i = 0; i < arraySize; i++) {
				if (i == 0) oss << data[i];
				else oss << "," << data[i];
			}
		}
		return oss.str();
	}

	/** friend output stream operator */
	friend std::ostream& operator<< (ostream& os, const QuickSort& myArray) {
		os << myArray.toString();
		return os;
	}
};

#endif