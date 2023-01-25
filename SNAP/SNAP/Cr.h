#ifndef CR_H
#define CR_H

#include <string>
#include <sstream>
#include "Course.h"

using namespace std;

class Cr : public Course {
public:
	Cr(string courseName, string room)
		: Course(courseName), room(room) {}
	virtual string toString() const {
		stringstream out;
		out << "cr(" << Course::toString() << "," << room << ")";
		return out.str();
	}
	friend ostream& operator<< (ostream& os, const Cr& cr) {
		os << cr.toString();
		return os;
	}
	string getRoom() { return room; } 
private:
	string room;
};

#endif