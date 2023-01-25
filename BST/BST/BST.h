#ifndef BST_H
#define BST_H

#include "BSTInterface.h"
#include <string>
#include <sstream>
using namespace std;

/** A binary tree node with data, left and right child pointers */
template<typename T>
class BST : public BSTInterface<T> {
private:
	struct Node {
		T data;
		Node* left;
		Node* right;
		Node(const T& d) : data(d), left(NULL), right(NULL) {}
	};
	Node* topRoot;
	size_t size;
public:
	BST(void) { 
		this->topRoot = NULL;
		size = 0;
	}
	virtual ~BST(void) { clearTree(); }

	/** Wrapper for addNode function */
	virtual bool addNode(const T& data) {
		return addNode(topRoot, data);
	}

	/** Return true if node added to BST, else false */
	bool addNode(Node*& node, const T& data) {
		if (node == NULL) {
			node = new Node(data);
			size++;
			return true;
		}
		else if (data == node->data) return false;
		else if (data < node->data) return addNode(node->left, data);
		else if (data > node->data) return addNode(node->right, data);
	}

	/** Returns the In-order predecessor of the node */
	Node* getPredecessor(Node* node) {
		Node* predecessor = node->left;
		while (predecessor->right) predecessor = predecessor->right;
		return predecessor;
	}

	/** Wrapper for removeNode function */
	virtual bool removeNode(const T& data) {
		return removeNode(topRoot, data);
	}

	/** Return true if node removed from BST, else false */
	virtual bool removeNode(Node*& node, const T& data) {
		if (node == NULL) return false;
		if (data < node->data) return removeNode(node->left, data);
		if (data > node->data) return removeNode(node->right, data);
		if (!node->left && !node->right) { //if node has no children
			Node* tempNode = node;
			node = NULL;
			delete tempNode;
			size--;
			return true;
		}
		if (node->left && !node->right) { //if node has only a left child
			Node* tempNode = node;
			node = node->left;
			delete tempNode;
			size--;
			return true;
		}
		if (!node->left && node->right) { //if node has only a right child
			Node* tempNode = node;
			node = node->right;
			delete tempNode;
			size--;
			return true;
		}
		swap(node->data, getPredecessor(node)->data); //if node has two children
		return removeNode(node->left, data);
	}

	/** Wrapper for clearTree function */
	virtual bool clearTree() {
		return clearTree(topRoot);
	}

	/** Return true if BST cleared of all nodes, else false */
	bool clearTree(Node*& root) {
		if (root == NULL) return true;
		if (clearTree(root->left) && clearTree(root->right)) {
			delete root;
			root = NULL;
			size = 0;
			return true;
		}
	}

	/** Wrapper for find function */
	bool find(const T& data) {
		return find(topRoot, data);
	}

	/** Return true if the value is found in the BST, else false */
	bool find(Node*& node, const T& data) {
		if (node == NULL) return false;
		if (node->data == data) return true;
		if (data < node->data) return find(node->left, data);
		if (data > node->data) return find(node->right, data);
	}

	/** Return the number of nodes in the tree */
	int getSize() {
		return size;
	}

	/** Output nodes at a given level */
	bool outLevel(Node* root, int level, stringstream& out) const {
		if (root == NULL) return false;
		if (level == 1) {
			out << " " << root->data;
			if ((root->left != NULL) || (root->right != NULL)) return true;
			return false;
		}
		if ((level == 2) && !root->left && root->right) out << " _";
		bool left = outLevel(root->left, level - 1, out);
		bool right = outLevel(root->right, level - 1, out);
		if ((level == 2) && root->left && !root->right) out << " _";
		return left || right;
	}

	/** Return a level order traversal of a BST as a string */
	virtual string toString() const {
		stringstream out;
		if (topRoot == NULL) out << " Empty";
		else {
			int level = 0;
			do {
				out << endl << "  " << ++level << ":";
			} while (outLevel(topRoot, level, out));
		}
		return out.str();

	}

	friend ostream& operator<< (ostream& os, const BST& myBST) {
		os << myBST.toString();
		return os;
	}
};

#endif