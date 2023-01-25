#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <sstream>

using namespace std;

class Course {
public:
	Course(string courseName) : courseName(courseName) {}
	virtual string toString() const {
		stringstream out;
		out << courseName;
		return out.str();
	}
	friend ostream& operator<< (ostream& os, const Course& course) {
		os << course.toString();
		return os;
	}
	string getCourseName() { return courseName; }
private:
	string courseName;
};

#endif