#ifndef HASHMAP_H
#define HASHMAP_H

#include "HashMapInterface.h"
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
using namespace std;

#define DEFAULT_MAP_HASH_TABLE_SIZE	31
#define HASH_CONSTANT				3
#define LOAD_THRESHOLD				75

template <typename K, typename V>
class HashMap : public HashMapInterface<K, V> {
private:
	pair<K, V>* myArray;
	size_t numKeys;
public:
	HashMap() { 
		myArray = new pair<K, V>[DEFAULT_MAP_HASH_TABLE_SIZE];
		numKeys = 0;
	}
	virtual ~HashMap() { clear(); }

	/** Hash function:
	s0 x 3^(n-1) + s2 x 3^(n-1) + ... + sn-1 */
	size_t hash(const string& s) {
		long long result = 0;
		for (size_t i = 0; i < s.length(); i++) result = result * HASH_CONSTANT + s[i];
		size_t hash = result % DEFAULT_MAP_HASH_TABLE_SIZE;
		return hash;
	}

	/** Read/write index access operator.
	If the key is not found, an entry is made for it.
	@return: Read and write access to the value mapped to the provided key. */
	virtual V& operator[](const K& key) {
		size_t index = hash(key);
		size_t k = -1;
		if ((myArray[index].first != key) && (numKeys >= DEFAULT_MAP_HASH_TABLE_SIZE-5)) { // hashmap is almost full!
			//rehash();
			return myArray[index].second;
		}
		while (myArray[index].first != "" && (myArray[index].first != key)) {
			k += 2;
			index = (index + k) % DEFAULT_MAP_HASH_TABLE_SIZE;
		}
		if (myArray[index].first != key) {
			myArray[index].first = key;
			myArray[index].second = V();
			numKeys++;
		}
		return myArray[index].second;
	}

	/** @return: the number of elements that match the key in the Map. */
	virtual size_t count(const K& key) {
		/*for (size_t i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++) {
			if (myArray[i].second.count(key) == 1) return 1;
		}*/
		return 0;
	}

	/** Removes all items from the Map. */
	virtual void clear() {
		numKeys = 0;
		delete[] myArray;
	}

	/** @return: number of Key-Value pairs stored in the Map. */
	virtual size_t size() const { return numKeys; }

	/** @return: maximum number of Key-Value pairs that the Map can hold. */
	virtual size_t max_size() const { return DEFAULT_MAP_HASH_TABLE_SIZE; }

	/** @return: string representation of Key-Value pairs in Map. */
	virtual std::string toString() const {
		ostringstream oss;
		for (size_t i = 0; i < DEFAULT_MAP_HASH_TABLE_SIZE; i++) {
			if (myArray[i].first != "") {
				oss << "  [" << i << ":" << myArray[i].first << "->" << myArray[i].second << "]" << endl;
			}
		}
		return oss.str();
	}

	/** friend output stream operator */
	friend std::ostream& operator<< (ostream& os, const HashMap& myHashMap) {
		os << myHashMap.toString();
		return os;
	}
};

#endif