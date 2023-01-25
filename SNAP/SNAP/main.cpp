/*
Manny Memorycheck

Code arranges student information into various outputs.
*/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include <iostream>
#include <vector>
#include <fstream>
#include "Cdh.h"
#include "Cr.h"
#include "Csg.h"
#include "Snap.h"

using namespace std;

int main(int argc, char * argv[]) {
	VS_MEM_CHECK

	#define CONSOLE 1

	cout << "Input File: " << argv[1];
	ifstream in(argv[1]);
	/*
	cout << endl << "Output File: " << (CONSOLE ? "cout" : argv[2]) << endl;
	ostream& out = CONSOLE ? cout : *(new ofstream(argv[2])); //tests[TEST_NUM].output)
	*/
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	ofstream out(argv[2]);
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	out << "Input Strings:";
	vector<Snap> snap;
	vector<Csg> csg;
	vector<Cdh> cdh;
	vector<Cr> cr;
	for (string line; getline(in, line);) {	// Read until EOF 
		if (line.size() == 0) continue;
		else if ("snap(" == line.substr(0, 5)) {
			// snap(12345,Charlie Brown,Manager,555-1234).
			out << endl << line;
			string studentID = line.substr(5, line.find(',') - 5);
			line = line.substr(line.find(',') + 1);
			string studentName = line.substr(0, line.find(','));
			line = line.substr(line.find(',') + 1);
			string studentAddress = line.substr(0, line.find(','));;
			line = line.substr(line.find(',') + 1);
			string studentPhone = line.substr(0, line.find(')'));
			snap.push_back(Snap(studentID, studentName, studentAddress, studentPhone));
		}
		else if ("csg(" == line.substr(0, 4)) {
			// csg(CS101,12345,A).
			out << endl << line;
			string courseName = line.substr(4, line.find(',') - 4);
			line = line.substr(line.find(',') + 1);
			string studentID = line.substr(0, line.find(','));
			line = line.substr(line.find(',') + 1);
			string studentGrade = line.substr(0, line.find(')')); // substr(0, line.find(')'));
			csg.push_back(Csg(studentID, courseName, studentGrade));
		}
		else if ("cdh(" == line.substr(0, 4)) {
			// cdh(CS101,M,9AM).
			out << endl << line;
			string courseName = line.substr(4, line.find(',') - 4);
			line = line.substr(line.find(',') + 1);
			string day = line.substr(0, line.find(','));
			line = line.substr(line.find(',') + 1);
			string time = line.substr(0, line.find(')'));
			cdh.push_back(Cdh(courseName, day, time));
		}
		else if ("cr(" == line.substr(0, 3)) {
			// cr('CS101','Turing Aud.').
			out << endl << line;
			string courseName = line.substr(3, line.find(',') - 3);
			line = line.substr(line.find(',') + 1);
			string room = line.substr(0, line.find(')'));
			cr.push_back(Cr(courseName, room));
		}
		else {
			try {
				throw line;
			}
			catch (string line) {
				out << endl << "**Error: " << line;
			}
		}
	}

	out << endl << endl << "Vectors:" << endl;
	for (unsigned int i = 0; i < snap.size(); i++){
		out << snap[i] << endl;
	}
	for (unsigned int i = 0; i < csg.size(); i++) {
		out << csg[i] << endl;
	}
	for (unsigned int i = 0; i < cdh.size(); i++) {
		out << cdh[i] << endl;
	}
	for (unsigned int i = 0; i < cr.size(); i++) {
		out << cr[i] << endl;
	}

	out << endl << "Course Grades:" << endl;
	for (unsigned int i = 0; i < csg.size(); i++) {
		out << csg.at(i).getCourseName() << " ";
		for (unsigned int j = 0; j < cdh.size(); j++) {
			if (csg.at(i).getCourseName() == cdh.at(j).getCourseName()) {
				out << cdh.at(j).getDay();
			}
		}
		out << ", ";
		for (unsigned int j = 0; j < cr.size(); j++) {
			if (csg.at(i).getCourseName() == cr.at(j).getCourseName()) {
				out << cr.at(j).getRoom();
				continue;
			}
		}
		out << ", ";
		for (unsigned int j = 0; j < snap.size(); j++) {
			if (csg.at(i).getStudentID() == snap.at(j).getStudentID()) {
				out << snap.at(j).getStudentName() << ", " << snap.at(j).getStudentID()
					<< ", " << csg.at(i).getStudentGrade();
				continue;
			}
		}
		if ((i < csg.size()-1) && (csg.at(i).getCourseName() != csg.at(i+1).getCourseName())) {
			out << endl;
		}
		out << endl;
	}

	out << endl << "Student Schedules:" << endl;
	for (unsigned int i = 0; i < snap.size(); i++) {
		out << snap.at(i).getStudentName() << ", " << snap.at(i).getStudentID() << ", "
			<< snap.at(i).getStudentAddress() << ", " << snap.at(i).getStudentPhone();
		for (unsigned int j = 0; j < csg.size(); j++) {
			if (csg.at(j).getStudentID() == snap.at(i).getStudentID()) {
				out << endl << "   " << csg.at(j).getCourseName() << " ";
				for (unsigned int k = 0; k < cdh.size(); k++) {
					if (cdh.at(k).getCourseName() == csg.at(j).getCourseName()) {
						out << cdh.at(k).getDay();
					}
				}
				for (unsigned int k = 0; k < cdh.size(); k++) {
					if (cdh.at(k).getCourseName() == csg.at(j).getCourseName()) {
						out << " " << cdh.at(k).getTime() << ", ";
						goto here;
					}
				}
				here:
				for (unsigned int k = 0; k < cr.size(); k++) {
					if (cr.at(k).getCourseName() == csg.at(j).getCourseName()) {
						out << cr.at(k).getRoom();
						continue;
					}
				}
			}
		}
		out << endl << endl;
	}

	system("pause");
	return 0;
}