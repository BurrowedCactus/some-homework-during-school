#ifndef BINARY_H
#define BINARY_H

#include <string>
#include <iostream>
#include "Expression.h"

using namespace std;

class Binary : public Expression{
	Expression* exp1;
	Expression* exp2;
	string method;
public:
	Binary(Expression* exp1, Expression* exp2, string method);
	void prettyprint();
	void unset(string var);
	int evaluate();
	void set(string var, int num);
	~Binary();
};

#endif
