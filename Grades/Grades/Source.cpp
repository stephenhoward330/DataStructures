/*
Ivy If-Else
Input: Student names and test scores
Output: Exam Averages, Student Grades, Exam Grades
*/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

//Takes the difference between the average and the percentage grade and returns a letter grade.
char differenceToGrade(double difference) {
	char grade;

	if (difference >= 0.0) {
		if (difference <= 5.0) {
			grade = 'C';
		}
		else if (difference < 15.0) {
			grade = 'B';
		}
		else {
			grade = 'A';
		}
	}
	else {
		if (difference >= -5.0) {
			grade = 'C';
		}
		else if (difference > -15.0) {
			grade = 'D';
		}
		else {
			grade = 'E';
		}
	}

	return grade;
}

int main(int argc, char* argv[]) {
	VS_MEM_CHECK

	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out) {
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}
	
	int numStudents;
	int numExams;
	in >> numStudents >> numExams;
	in.ignore(std::numeric_limits<int>::max(), '\n');

	string *students = new string[numStudents];
	int **scores = new int*[numStudents];
	for (int i = 0; i < numStudents; ++i) {
		scores[i] = new int[numExams];
	}

	string line1;
	string line2;
	string firstName;
	string lastName;
	for (int i = 0; i < numStudents; ++i) {
		in >> firstName >> lastName;
		line1 = firstName + " " + lastName;
		students[i] = line1;
		getline(in, line2);
		size_t p = 0;
		while (!isdigit(line2[p])) ++p;
		line2 = line2.substr(p);
		istringstream iss(line2);
		for (int j = 0; j < numExams; ++j) {
			iss >> scores[i][j];
		}
	}

	int total;
	double *examAverages = new double[numExams];
	for (int i = 0; i < numExams; i++) {
		total = 0;
		for (int j = 0; j < numStudents; j++) {
			total += scores[j][i];
		}
		examAverages[i] = (total * 1.0) / numStudents;
	}
	double *studentAverages = new double[numStudents];
	for (int i = 0; i < numStudents; i++) {
		total = 0;
		for (int j = 0; j < numExams; j++) {
			total += scores[i][j];
		}
		studentAverages[i] = (total * 1.0) / numExams;
	}

	out << "Student Scores:" << endl;
	for (int i = 0; i < numStudents; ++i) {
		out << setw(20) << students[i] << " ";
		for (int j = 0; j < numExams; ++j) {
			out << fixed << setprecision(0) << setw(6);
			out << scores[i][j];
		}
		out << endl;
	}

	out << "Exam Averages:" << endl;
	for (int i = 0; i < numExams; i++) {
		out << setw(8) << "Exam " << i+1 << " Average =";
		out << setw(6) << fixed << setprecision(1) << examAverages[i] << endl;
	}

	double difference;
	out << "Student Exam Grades:" << endl;
	for (int i = 0; i < numStudents; ++i) {
		out << setw(20) << students[i] << " ";
		for (int j = 0; j < numExams; ++j) {
			out << fixed << setprecision(0) << setw(6);
			out << scores[i][j] << "(";
			difference = scores[i][j] - examAverages[j];
			out << differenceToGrade(difference) << ")";
		}
		out << endl;
	}

	int numA;
	int numB;
	int numC;
	int numD;
	int numE;
	out << "Exam Grades:" << endl;
	for (int i = 0; i < numExams; i++) {
		numA = 0;
		numB = 0;
		numC = 0;
		numD = 0;
		numE = 0;
		for (int j = 0; j < numStudents; j++) {
			difference = scores[j][i] - examAverages[i];
			if (differenceToGrade(difference) == 'A') {
				numA += 1;
			}
			if (differenceToGrade(difference) == 'B') {
				numB += 1;
			}
			if (differenceToGrade(difference) == 'C') {
				numC += 1;
			}
			if (differenceToGrade(difference) == 'D') {
				numD += 1;
			}
			if (differenceToGrade(difference) == 'E') {
				numE += 1;
			}
		}
		out << setw(8) << "Exam  " << i + 1 << "\t" << numA << "(A)\t" << numB << "(B)\t" << numC << "(C)\t"
			<< numD << "(D)\t" << numE << "(E)\t" << endl;
	}

	double classAverage = 0;
	for (int i = 0; i < numStudents; i++) {
		classAverage += studentAverages[i];
	}
	classAverage = classAverage / numStudents;
	out << "Student Final Grades:" << endl;
	for (int i = 0; i < numStudents; ++i) {
		out << setw(20) << students[i] << " ";
		out << fixed << setprecision(1) << setw(6) << studentAverages[i] << "(";
		out << differenceToGrade(studentAverages[i] - classAverage) << ")" << endl;
	}
	out << "Class Average Score = " << fixed << setprecision(1) << classAverage << endl;

	for (int i = 0; i < numStudents; ++i) {
		delete[] scores[i];
	}
	delete[] scores;
	delete[] students;
	delete[] studentAverages;
	delete[] examAverages;

	return 0;
}