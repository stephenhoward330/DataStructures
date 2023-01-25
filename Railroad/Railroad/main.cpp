/*
Tony turntable
Program takes incoming trains and puts them on a turntable, then onto a queue or a stack,
then returns them to an outgoing train vector
*/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Station.h"
using namespace std;

int main(int argc, char * argv[]) {
	VS_MEM_CHECK

	ifstream in(argv[1]);
	ofstream out(argv[2]);
	Station<unsigned int> myStation;
	unsigned int inputNum; //train number
	int output; //output of some int functions
	string garbo; //placeholder; useless string

	string line;
	while (getline(in, line)) {
		if (line.find("Add:station") != string::npos) {
			istringstream iss(line);
			iss >> garbo >> inputNum;
			if (myStation.setTurntable(inputNum)) {
				out << line << " OK" << endl;
			}
			else out << line << " Turntable occupied!" << endl;
		}
		else if (line.find("Add:queue") != string::npos) {
			if (myStation.addQueue()) {
				out << line << " OK" << endl;
			}
			else out << line << " Turntable empty!" << endl;
		}
		else if (line.find("Add:stack") != string::npos) {
			if (myStation.addStack()) {
				out << line << " OK" << endl;
			}
			else out << line << " Turntable empty!" << endl;
		}
		else if (line.find("Remove:station") != string::npos) {
			if (myStation.removeStation()) {
				out << line << " OK" << endl;
			}
			else out << line << " Turntable empty!" << endl;
		}
		else if (line.find("Remove:queue") != string::npos) {
			output = myStation.removeQueue();
			if (output == 0) out << line << " Queue empty!" << endl;
			else if (output == 1) out << line << " Turntable occupied!" << endl;
			else out << line << " OK" << endl;
		}
		else if (line.find("Remove:stack") != string::npos) {
			output = myStation.removeStack();
			if (output == 0) out << line << " Stack empty!" << endl;
			else if (output == 1) out << line << " Turntable occupied!" << endl;
			else out << line << " OK" << endl;
		}
		else if (line.find("Top:station") != string::npos) {
			if (myStation.getTurntable() == 0) out << line << " Turntable empty!" << endl;
			else out << line << " " << myStation.getTurntable() << endl;
		}
		else if (line.find("Top:queue") != string::npos) {
			if (myStation.topQueue() == -1) out << line << " Queue empty!" << endl;
			else out << line << " " << myStation.topQueue() << endl;
		}
		else if (line.find("Top:stack") != string::npos) {
			if (myStation.topStack() == -1) out << line << " Stack empty!" << endl;
			else out << line << " " << myStation.topStack() << endl;
		}
		else if (line.find("Size:queue") != string::npos) {
			out << line << " " << myStation.sizeQueue() << endl;
		}
		else if (line.find("Size:stack") != string::npos) {
			out << line << " " << myStation.sizeStack() << endl;
		}
		else if (line.find("Train:") != string::npos) {
			out << line << " " << myStation.trainContents() << endl;
		}
	}

	system("pause");
	return 0;
}