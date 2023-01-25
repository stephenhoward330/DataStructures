#ifndef SET_H
#define SET_H

#include <string>
#include <sstream>
#include <list>
#include "SetInterface.h"
using namespace std;

template<typename T>
class Set : public SetInterface<T> {
private:
	list<T> myList;
public:
	Set() {}
	~Set() { myList.clear(); }

	/** Inserts item into the set, if the container doesn't
	already contain an element with an equivalent value.
	@return: pair.first = pointer to item
	pair.second = true if successfully inserted, else false. */
	//virtual Pair<T*, bool> insert(const T& item) = 0;
	virtual bool insert(const T& item) { 
		myList.push_back(item);
		myList.unique();
		myList.sort();
		return true;
	}

	/** Removes all items from the set. */
	virtual void clear() { myList.clear(); }

	/** @return: the number of elements contained by the Set. */
	virtual size_t size() const { return myList.size(); }

	/** @return: return 1 if contains element equivalent to item, else 0. */
	virtual size_t count(const T& item) {
		for (list<string>::const_iterator iter = myList.begin(); iter != myList.end(); ++iter) {
			if (*iter == item) return 1;
		}
		return 0;
	}

	/** @return: string representation of items in Set. */
	virtual std::string toString() const {
		ostringstream oss;
		for (list<string>::const_iterator iter = myList.begin(); iter != myList.end(); ++iter) {
			if (iter != myList.begin()) {
				oss << "," << *iter;
			}
			else oss << *iter;
		}
		return oss.str();
	}

	/** friend output stream operator */
	friend std::ostream& operator<< (ostream& os, const Set& mySet) {
		os << mySet.toString();
		return os;
	}
};

#endif