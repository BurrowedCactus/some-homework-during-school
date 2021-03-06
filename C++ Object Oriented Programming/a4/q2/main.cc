#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Expression.h"
#include "Integer.h"
#include "Variable.h"
#include "Unary.h"
#include "Binary.h"

using namespace std;

int main(){
	string input;
	int number;
	vector<Expression*> stack;
	while (cin >> input){
		istringstream iss {input};
		if (iss >> number){
			stack.emplace_back(new Integer {number});
		} else if (input == "NEG" || input == "ABS"){
			stack.back() = new Unary (stack.back(), input);
		} else if (input == "+" || input == "-" || input == "*" || input == "/"){
			Expression* temp = stack.back();
			stack.pop_back();
			stack.back() = new Binary {stack.back(), temp, input};
		} else if (input != "done"){
			stack.emplace_back(new Variable {0, input, false});
		} else {
			break;
		}
	}
	Expression* exp = stack.back();
	cout << exp->prettyprint() << endl;
	while (cin >> input){
		if (input == "eval"){
			try {
				cout << exp->evaluate() << endl;
			} catch (string s){
				cout << s << " has no value." << endl;
			}
		} else if (input == "print"){
			cout << exp->prettyprint() << endl;
		} else if (input == "set"){
			cin >> input;
			cin >> number;
			exp->set(input, number);
		} else if (input == "unset"){
			cin >> input;
			exp->unset(input);
		} else if (input == "copy"){
			Expression* theCopy = exp->copy();
			cout << theCopy->prettyprint() << endl;
			theCopy->set("x", 1);
			cout << theCopy->prettyprint() << endl;
			cout << theCopy->evaluate() << endl;
			delete theCopy;
		} else {
			continue;
		}
	}
	delete exp;
}


