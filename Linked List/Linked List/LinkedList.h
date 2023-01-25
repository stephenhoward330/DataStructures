#ifndef LINKED_LIST_H
#define LINKED_LIST_H
using std::string;
using std::ostream;
#include<sstream>

#include "LinkedListInterface.h"

template<typename T>
class LinkedList : public LinkedListInterface<T>
{
private:
	struct Node
	{
		T data;
		Node* next;
		Node(const T& d) : data(d), next(NULL) {}
		Node(const T& d, Node* n) : data(d), next(n) {}
	};
	Node* head;

public:
	LinkedList() { this->head = NULL; }
	~LinkedList() { clear(); }

	bool duplicateCheck(T value) {
		Node* nodePtr = head;
		while (nodePtr != NULL) {
			if (nodePtr->data == value) return true;
			nodePtr = nodePtr->next;
		}
		return false;
	}

	/** Insert Node at beginning of list (no duplicates) */
	virtual bool insertHead(T value) { 
		if (duplicateCheck(value)) return false;
		Node* nodePtr = head;
		head = new Node(value);
		if (nodePtr == NULL) {
			head->next = NULL;
		}
		else {
			head->next = nodePtr;
		}

		return true;
	}

	/** Insert Node at end of list (no duplicates) */
	virtual bool insertTail(T value) {
		if (duplicateCheck(value)) return false;
		if (head == NULL) {
			insertHead(value);
		}
		else {
			Node* nodePtr = head;
			Node* tail = new Node(value);
			while (nodePtr->next != NULL) {
				nodePtr = nodePtr->next;
			}
			nodePtr->next = tail;
		}
		return true;
	}

	/** Insert node after matchNode (no duplicates) */
	virtual bool insertAfter(T matchNode, T node) {
		if (duplicateCheck(node)) return false;
		if (head == nullptr) {
			return false;
		}
		Node* nodePtr = head;
		while (nodePtr->data != matchNode) {
			nodePtr = nodePtr->next;
			if (nodePtr == nullptr) {
				return false;
			}
		}
		Node* newNode = new Node(node);
		newNode->next = nodePtr->next;
		nodePtr->next = newNode;
		return true;
	}

	/** Remove Node from linked list */
	virtual bool remove(T value) {
		if (head == nullptr) { 
			return false;
		}
		if (head->data == value) {
			Node* ptr = head; // Point to node to be deleted
			head = ptr->next; // Remove Node from list
			delete ptr;
			return true;
		}
		Node* nodePtr = head;
		while (nodePtr->next->data != value) {
			nodePtr = nodePtr->next;
			if (nodePtr->next == nullptr) {
				return false;
			}
		}

		Node* ptr = nodePtr->next;     // Point to node to be deleted
		nodePtr->next = ptr->next;     // Remove Node from list
		delete ptr;
		
		return true;
	}

	/** Remove all Nodes from linked list */
	virtual bool clear() { 
		while (head != nullptr) {
			remove(head->data);
		}
		return true;
	}

	/** Return Node at index (0 based) */
	virtual bool at(int index, string& value) {
		if ((index < 0) || (index >= size())) {
			return false;
		}
		Node* nodePtr = head;
		for (int i = 0; i < index; i++) {
			nodePtr = nodePtr->next;
		}
		value = nodePtr->data;

		return true;
	}

	/** Returns the number of nodes in the linked list */
	virtual int size() const {
		int size = 0;
		Node* nodePtr = head;
		if (head == NULL) {
			return 0;
		}
		while (nodePtr != NULL) {
			size += 1;
			nodePtr = nodePtr->next;
		}
		return size;
	}

	string toString() const {
		std::stringstream oss;
		Node* nodePtr = head;
		if (head == nullptr) {
			return "Empty";
		}
		//oss << head->data;
		while (nodePtr != NULL) {
			oss << nodePtr->data << " ";
			nodePtr = nodePtr->next;
		}
		return oss.str();
	}

	void printList() const {
		//cout << toString() << endl;
	}

	friend ostream& operator<< (ostream& os, const LinkedList& list) {
		os << list.toString();
		return os;
	}
};
#endif   // LINKED_LIST_H