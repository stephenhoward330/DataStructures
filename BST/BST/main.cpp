/*
Barney Binary <(O(oo)O)>
This program creates a binary search tree for either Ints or Strings.
*/

#include "BST.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char * argv[]) {
	VS_MEM_CHECK    // enable memory leak check
					
	ifstream in(argv[1]);
	ofstream out(argv[2]);

	string line, input, type, stringVal;
	int intVal;
	BST<int> myBST;

	in >> type;
	if (type == "INT") { // If it's a BST for ints
		typeInt:
		myBST.clearTree();
		BST<int> myBST;
		out << "INT true" << endl;
		while (getline(in, line)) {
			istringstream iss(line);
			iss >> input;
			if (input == "INT") goto typeInt;
			else if (input == "STRING") goto typeString;
			else if (input == "add") {
				iss >> intVal;
				out << "add " << intVal << " ";
				if (myBST.addNode(intVal)) out << "true" << endl;
				else out << "false" << endl;
			}
			else if (input == "remove") {
				iss >> intVal;
				out << "remove " << intVal << " ";
				if (myBST.removeNode(intVal)) out << "true" << endl;
				else out << "false" << endl;
			}
			else if (input == "print") {
				out << "print:" << myBST << endl;
			}
			else if (input == "clear") {
				out << "clear "; 
				if (myBST.clearTree()) out << "true" << endl;
				else out << "false" << endl;
			}
			else if (input == "size") {
				out << "size " << myBST.getSize() << endl;
			}
			else if (input == "find") {
				iss >> intVal;
				out << "find " << intVal << " ";
				if (myBST.find(intVal)) out << "Found" << endl;
				else out << "Not Found" << endl;
			}
		}
	}
	if (type == "STRING") { // if it's a BST for strings
	typeString:
		myBST.clearTree();
		BST<string> myBST;
		out << "STRING true" << endl;
		while (getline(in, line)) {
			istringstream iss(line);
			iss >> input;
			if (input == "INT") goto typeInt;
			else if (input == "STRING") goto typeString;
			else if (input == "add") {
				iss >> stringVal;
				out << "add " << stringVal << " ";
				if (myBST.addNode(stringVal)) out << "true" << endl;
				else out << "false" << endl;
			}
			else if (input == "remove") {
				iss >> stringVal;
				out << "remove " << stringVal << " ";
				if (myBST.removeNode(stringVal)) out << "true" << endl;
				else out << "false" << endl;
			}
			else if (input == "print") {
				out << "print:" << myBST << endl;
			}
			else if (input == "clear") {
				out << "clear ";
				if (myBST.clearTree()) out << "true" << endl;
				else out << "false" << endl;
			}
			else if (input == "size") {
				out << "size " << myBST.getSize() << endl;
			}
			else if (input == "find") {
				iss >> stringVal;
				out << "find " << stringVal << " ";
				if (myBST.find(stringVal)) out << "Found" << endl;
				else out << "Not Found" << endl;
			}
		}
	}

	return 0;
}