/*
Irving Iterator
Outputs input numbers into various formats
*/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include<iostream>
#include<fstream>
#include "MyArray.h"

using namespace std;

//determines if a number is prime
bool isPrime(int number) {
	int i;
	if (number < 2) return false;
	for (i = 2; i < number; ++i)
	{
		if (number % i == 0) return false;
	}
	return true;
}

int main(int argc, char * argv[]) {
	VS_MEM_CHECK

	MyArray<int> numbers(MAX_ARRAY_SIZE);
	int i;
	ifstream in(argv[1]);
	while (in >> i) {
		numbers.push_back(i);
	}
	ofstream out(argv[2]);

	MyArray<int>::Iterator iter = numbers.begin();
	out << numbers << endl << endl;

	out << "ITERATORS:" << endl;
	out << "begin(): size=" << numbers.getSize() << " index=" << numbers.begin().getIndex() << endl;
	out << "end(): size=" << numbers.getSize() << " index=" << numbers.end().getIndex() << endl << endl;

	out << "SEQUENTIAL:";
	for (size_t i = 0; iter != numbers.end(); ++iter, i++) {
		if (!(i % 10)) out << endl;
		out << iter << " ";
	}
	out << endl << endl;

	out << "PRIME:" << endl;
	iter = numbers.begin();
	int j = 0;
	for (size_t i = 0; iter != numbers.end(); ++iter, i++) {
		if (isPrime(*iter)) {
			out << iter << " ";
			++j;
			if (!(j % 10)) out << endl;
		}
	}
	out << endl << endl;

	out << "COMPOSITE:" << endl;
	iter = numbers.begin();
	j = 0;
	for (size_t i = 0; iter != numbers.end(); ++iter, i++) {
		if (!isPrime(*iter)) {
			out << iter << " ";
			++j;
			if (!(j % 10)) out << endl;
		}
	}
	out << endl << endl;

	int v1 = 0;
	int v2 = 0;
	int v3 = 0;
	out << "FIBONACCI:" << endl;
	iter = numbers.begin();
	for (size_t i = 0; iter != numbers.end(); ++iter, i++) {
		v1 = v2;
		v2 = v3;
		v3 = *iter;
		if ((i > 1) && (v3 == (v1 + v2))) { //this if is only valid once i > 1 (once v1 = the first element)
			out << v3 << " = " << v1 << " + " << v2 << endl;
		}
	}
	out << endl;

	system("pause");
	return 0;
}