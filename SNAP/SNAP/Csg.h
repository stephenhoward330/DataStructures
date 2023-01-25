#ifndef CSG_H
#define CSG_H

#include <string>
#include <sstream>
#include "Course.h"

using namespace std;

class Csg : public Course {
public:
	Csg(string studentID, string courseName, string studentGrade)
		: studentID(studentID), Course(courseName), studentGrade(studentGrade) {}
	virtual string toString() const {
		stringstream out;
		out << "csg(" << Course::toString() << "," << studentID << "," << studentGrade << ")";
		return out.str();
	}
	friend ostream& operator<< (ostream& os, const Csg& csg) {
		os << csg.toString();
		return os;
	}
	string getStudentID() { return studentID; }
	string getStudentGrade() { return studentGrade; }
private:
	string studentID;
	string studentGrade;
};

#endif