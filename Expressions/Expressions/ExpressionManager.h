#ifndef EXPRESSION_MANAGER_H
#define EXPRESSION_MANAGER_H
#include "ExpressionManagerInterface.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

class ExpressionManager : public ExpressionManagerInterface {
private:
	string expression;
	vector<char> inFix;
	vector<string> postFix;
	vector<string> preFix;
	vector<int> values;
	const string operators = "-+*/%";

	const string open = "([{";	// set of opening parentheses
	const string close = ")]}";	// corresponding closing parentheses.

	/** Function to determine if open parentheses */
	bool isOpen(char ch) {
		return open.find(ch) != string::npos;
	}

	/** Function to determine if closing parentheses */
	bool isClose(char ch) {
		return close.find(ch) != string::npos;
	}

	// Function to determine if inFix is balanced
	bool isBalanced() { //const string& expression
		bool balanced = true;
		string::const_iterator iter = expression.begin();
		while (balanced && (iter != expression.end())) {
			char nextCh = *iter;
			if (isOpen(nextCh)) inFix.push_back(nextCh);
			else {
				if (isClose(nextCh)) {
					if (inFix.empty()) balanced = false;
					else {
						char topCh = inFix.back();
						inFix.pop_back();
						balanced = open.find(topCh) == close.find(nextCh);
					}
				}
			}
			++iter;
		}
		return balanced && inFix.empty();
	}

	// Function to determine if infix is missing an operator or operand
	string isProper() {
		string::const_iterator iter = expression.begin();
		char firstCh = *iter;
		if (operators.find(firstCh) != string::npos) {
			return "Missing Operand";
		}
		++iter;
		if (iter == expression.end()) return "All good";
		++iter;
		if (iter != expression.end()) {
			while (isspace(*iter)) {
				++iter;
			}
		}
		while (iter != expression.end()) {
			char secondCh = *iter;
			while (isOpen(secondCh) || isClose(secondCh)) {
				++iter;
				if (iter == expression.end()) {
					return "All good";
				}
				++iter;
				secondCh = *iter;
			}
			if (isdigit(firstCh) && isdigit(secondCh)) {
				return "Missing Operator";
			}
			if ((operators.find(firstCh) != string::npos) && (operators.find(secondCh) != string::npos)) {
				return "Missing Operand";
			}
			if (!isdigit(secondCh) && operators.find(secondCh) == string::npos) {
				return "Illegal Operator";
			}
			firstCh = secondCh;
			++iter;
			while (iter != expression.end() && isdigit(*iter)) {
				++iter;
			}
			if (iter != expression.end()) {
				if (isspace(*iter)) {
					++iter;
				}
			}
		}
		if (operators.find(firstCh) != string::npos) {
			return "Missing Operand";
		}
		return "All good";
	}

	// Function to determine precedence level of operators
	int getPrecedence(string token) {
		int precedence = 0;
		if (token.at(0) == '+' || token.at(0) == '-') {
			precedence = 1;
		}
		else if (token.at(0) == '*' || token.at(0) == '/' || token.at(0) == '%') {
			precedence = 2;
		}
		else if (isOpen(token.at(0)) || isClose(token.at(0))) {
			precedence = 0;
		}
		return precedence;
	}

	// Function to reverse expression string and swap opening and closing parens
	void reverseExpression()
	{
		int n = expression.length();

		for (int i = 0; i < n / 2; i++) { // reverse expression
			swap(expression[i], expression[n - i - 1]);
		}

		for (int i = 0; i < n; i++) { // swap opening and closing parens
			if (isOpen(expression[i])) {
				expression[i] = close[open.find(expression[i])];
			}
			else if (isClose(expression[i])) {
				expression[i] = open[close.find(expression[i])];
			}
		}
	}

public:
	//ExpressionManager() { }
	ExpressionManager(string exp) : expression(exp), inFix(NULL), postFix(NULL), preFix(NULL) { }
	~ExpressionManager() { }

	/** Return the integer value of the infix expression */
	virtual int value(void) {
		string postFixExpression = postfix();
		istringstream iss(postFixExpression);
		string token;
		int intToken = 0;
		int var1 = 0;
		int var2 = 0;
		while (iss >> token) {
			if (isdigit(token.at(0))) {
				stringstream convert(token);
				int intToken = 0;
				convert >> intToken;
				values.push_back(intToken);
				var1 = intToken;
			}
			else {
				var2 = values.back();
				values.pop_back();
				var1 = values.back();
				values.pop_back();
				if (token == "+") var1 += var2;
				else if (token == "-") var1 -= var2;
				else if (token == "*") var1 *= var2;
				else if (token == "/") var1 /= var2;
				else if (token == "%") var1 %= var2;
				values.push_back(var1);
			}
		}
		return var1;
	}

	/** Return the infix expression / rejects invalid */
	virtual string infix(void) {
		if (!isBalanced()) {
			return "Unbalanced";
		}
		if (isProper() == "Missing Operand") {
			return "Missing Operand";
		}
		if (isProper() == "Missing Operator") {
			return "Missing Operator";
		}
		if (isProper() == "Illegal Operator") {
			return "Illegal Operator";
		}
		return expression;
	}

	/** Return a postfix representation */
	virtual string postfix(void) {
		string output;
		istringstream iss(expression);
		string token;
		while (iss >> token) {
			if (isdigit(token.at(0))) {
				output.append(token);
				output.append(" ");
			}
			else if (isOpen(token.at(0))) {
				postFix.push_back(token);
			}
			else if (isClose(token.at(0))) {
				while (close.find(token) != open.find(postFix.back())) {
					if (postFix.size() == 0) {
						return "Unbalanced";
					}
					else if (isOpen(postFix.back().at(0))) {
						return "Unbalanced";
					}
					output.append(postFix.back());
					output.append(" ");
					postFix.pop_back();
				}
				postFix.pop_back();
			}
			else if (postFix.size() == 0) {
				postFix.push_back(token);
			}
			else if (getPrecedence(token) > getPrecedence(postFix.back())) {
				postFix.push_back(token);
			}
			else if (getPrecedence(token) <= getPrecedence(postFix.back())) {
				while (getPrecedence(token) <= getPrecedence(postFix.back())) {
					output.append(postFix.back());
					output.append(" ");
					postFix.pop_back();
					if (postFix.size() == 0) break;
				}
				postFix.push_back(token);
			}
		}
		while (postFix.size() != 0) {
			output.append(postFix.back());
			output.append(" ");
			postFix.pop_back();
		}
		return output;
	}
	
	/** (BONUS) Return a prefix representation */
	virtual string prefix(void) { /** (BONUS) Return a prefix representation */
		reverseExpression();

		string output;
		istringstream iss(expression);
		string token;
		while (iss >> token) {
			if (isdigit(token.at(0))) {
				output.append(token);
				output.append(" ");
			}
			else if (isOpen(token.at(0))) {
				postFix.push_back(token);
			}
			else if (isClose(token.at(0))) {
				while (close.find(token) != open.find(postFix.back())) {
					if (postFix.size() == 0) {
						return "Unbalanced";
					}
					else if (isOpen(postFix.back().at(0))) {
						return "Unbalanced";
					}
					output.append(postFix.back());
					output.append(" ");
					postFix.pop_back();
				}
				postFix.pop_back();
			}
			else if (postFix.size() == 0) {
				postFix.push_back(token);
			}
			else if (getPrecedence(token) >= getPrecedence(postFix.back())) {
				postFix.push_back(token);
			}
			else if (getPrecedence(token) < getPrecedence(postFix.back())) {
				while (getPrecedence(token) < getPrecedence(postFix.back())) {
					output.append(postFix.back());
					output.append(" ");
					postFix.pop_back();
					if (postFix.size() == 0) break;
				}
				postFix.push_back(token);
			}
		}
		while (postFix.size() != 0) {
			output.append(postFix.back());
			output.append(" ");
			postFix.pop_back();
		}

		expression = output;
		reverseExpression();
		return expression;
	}

	// NOT IMPLEMENTED
	virtual string toString() const {
		return "NOT IMPLEMENTED";
	}
};

#endif // EXPRESSION_MANAGER_H
