#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <iostream>
#include "Expression.h"

using namespace std;

class Variable : public Expression{
private:
	int value;
	string name;
	bool isSet;
public:
	Variable(int value, string name, bool isSet);
	void prettyprint();
	void unset(string var);
	int evaluate();
	void set(string var, int num);
};

#endif
