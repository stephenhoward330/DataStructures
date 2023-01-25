#ifndef CDH_H
#define CDH_H

#include <string>
#include <sstream>
#include "Course.h"

using namespace std;

class Cdh : public Course {
public:
	Cdh(string courseName, string day, string time)
		: Course(courseName), day(day), time(time) {}
	virtual string toString() const {
		stringstream out;
		out << "cdh(" << Course::toString() << "," << day << "," << time << ")";
		return out.str();
	}
	friend ostream& operator<< (ostream& os, const Cdh& cdh) {
		os << cdh.toString();
		return os;
	}
	string getDay() { return day; }
	string getTime() { return time; }
private:
	string day;
	string time;
};

#endif