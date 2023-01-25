#ifndef SNAP_H
#define SNAP_H

#include <string>
#include <sstream>

using namespace std;

class Snap {
public:
	Snap(string studentID, string studentName, string studentAddress, string studentPhone)
		: studentID(studentID), studentName(studentName), studentAddress(studentAddress), studentPhone(studentPhone) {}
	virtual string toString() const {
		stringstream out;
		out << "snap(" << studentID << "," << studentName << "," << studentAddress << "," << studentPhone << ")";
		return out.str();
	}
	friend ostream& operator<< (ostream& os, const Snap& snap) {
		os << snap.toString();
		return os;
	}
	string getStudentID() { return studentID; }
	string getStudentName() { return studentName; }
	string getStudentAddress() { return studentAddress; }
	string getStudentPhone() { return studentPhone; }
private:
	string studentID;
	string studentName;
	string studentAddress;
	string studentPhone;
};

#endif