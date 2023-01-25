/*
Kirby Coder (>'.')>
Program is capable of quicksorting a dynamic array.
*/

#include "QuickSort.h"
#include <fstream>
#include <sstream>
#include <iostream>

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

int main(int argc, char * argv[])
{
	VS_MEM_CHECK
	
	ifstream in(argv[1]);
	ofstream out(argv[2]);

	string line, input;
	int num1, num2, num3;
	QuickSort<int> quickSort;

	while (getline(in, line)) {
		istringstream iss(line);
		iss >> input;
		if (input == "QuickSort") {
			iss >> num1;
			quickSort.createArray(num1);
			out << input << " " << num1 << " OK" << endl;
		}
		else if (input == "Capacity") {
			out << input << " " << quickSort.capacity() << endl;
		}
		else if (input == "Size") {
			out << input << " " << quickSort.size() << endl;
		}
		else if (input == "Clear") {
			quickSort.clear();
			out << input << " OK" << endl;
		}
		else if (input == "AddToArray") {
			out << input << " ";
			iss >> num1;
			out << num1;
			quickSort.addElement(num1);
			while (iss >> num1) {
				out << "," << num1;
				quickSort.addElement(num1);
			}
			out << " OK" << endl;
		}
		else if (input == "PrintArray") {
			out << input << " " << quickSort << endl;
		}
		else if (input == "MedianOfThree") {
			iss >> num1 >> num2;
			int middle = quickSort.medianOfThree(num1, num2);
			out << input << " " << num1 << "," << num2 << " = " << middle << endl;
		}
		else if (input == "Partition") {
			iss >> num1 >> num2 >> num3;
			int location = quickSort.partition(num1, num2, num3);
			out << input << " " << num1 << "," << num2 << "," << num3 << " = " << location << endl;
		}
		else if (input == "Sort") {
			iss >> num1 >> num2;
			quickSort.sort(num1, num2);
			out << input << " " << num1 << "," << num2 << " OK" << endl;
		}
		else if (input == "SortAll") {
			quickSort.sortAll();
			out << input << " OK" << endl;
		}
	}

	return 0;
}