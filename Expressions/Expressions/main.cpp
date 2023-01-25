/*
Eli ExpressionManager
Programs turns expressions into postfix and checks for balance errors.
*/

#include "ExpressionManager.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char * argv[]) {
	ifstream in(argv[1]);
	ofstream out(argv[2]);

	string line, command, expression;
	while (getline(in, line)) {
		try {
			if (line.size() == 0) continue;
			istringstream iss(line);
			iss >> command;
			ExpressionManager myExpressionManager(expression);
			if (command == "Expression:") {
				out << endl << line << endl;
				expression = line.substr(line.find(":") + 2);
			}
			else if (command == "Infix:") {
				out << "Infix: " << myExpressionManager.infix() << endl;
			}
			else if (command == "Postfix:") {
				out << "Postfix: " << myExpressionManager.postfix() << endl;
			}
			else if (command == "Prefix:") {
				out << "Prefix:" << myExpressionManager.prefix() << endl;
			}
			else if (command == "Value:") {
				out << "Value: " << myExpressionManager.value() << endl;
			}
			else out << "Illegal command" << endl;
			continue;
		}
		catch (std::exception& e) {
			out << e.what() << endl;
		}
	}

	system("pause");
	return 0;
}