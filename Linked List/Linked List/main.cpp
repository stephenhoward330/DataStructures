/*
John Coder
Lab 4 - Linked List
*/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include <fstream>
#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

/*
template<typename T>
T value;
template<class T2>
LinkedList<T2> myLinkedList;
*/

int main(int argc, char * argv[])
{
	VS_MEM_CHECK

	ifstream in(argv[1]);
	ofstream out(argv[2]);

	LinkedList<string> myLinkedList;
	string value1, value2;
	string input, line;

	while (getline(in, line)) {
		istringstream iss(line);
		iss >> input;
		if (input == "INT") {
			//LinkedList<int> myLinkedList;
			myLinkedList.clear();
			//int value1, value2;
			out << "INT true" << endl;
		}
		else if (input == "STRING") {
			//LinkedList<string> myLinkedList;
			myLinkedList.clear();
			string value1, value2;
			out << "STRING true" << endl;
		}

		else if (input == "insertHead") {
			iss >> value1;
			out << "insertHead " << value1 << " ";
			if (myLinkedList.insertHead(value1)) {
				out << "true" << endl;
			}
			else out << "false" << endl;
		}
		else if (input == "insertTail") {
			iss >> value1;
			out << "insertTail " << value1 << " ";
			if (myLinkedList.insertTail(value1)) {
				out << "true" << endl;
			}
			else out << "false" << endl;
		}
		else if (input == "insertAfter") {
			iss >> value1 >> value2;
			out << "insertAfter " << value1 << " " << value2 << " ";
			if (myLinkedList.insertAfter(value1, value2)) {
				out << "true" << endl;
			}
			else out << "false" << endl;
		}
		else if (input == "remove") {
			iss >> value1;
			out << "remove " << value1 << " ";
			if (myLinkedList.remove(value1)) {
				out << "true" << endl;
			}
			else out << "false" << endl;
		}
		else if (input == "clear") {
			out << "clear ";
			if (myLinkedList.clear()) {
				out << "true" << endl;
			}
			else out << "false" << endl;
		}
		else if (input == "at") {
			int index;
			iss >> index;
			out << "at " << index << " ";
			if (myLinkedList.at(index, value1)) {
				out << value1 << " true" << endl;
			}
			else out << "Invalid Index" << endl;
		}
		else if (input == "size") {
			out << "size " << myLinkedList.size() << endl;
		}
		else if (input == "printList") {
			out << "printList " << myLinkedList << endl;
		}
	}

	system("pause");
	return 0;
}