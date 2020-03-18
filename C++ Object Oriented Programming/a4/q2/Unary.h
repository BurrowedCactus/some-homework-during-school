#ifndef UNARY_H
#define UNARY_H

#include <string>
#include <iostream>

using namespace std;

class Unary : public Expression{
	Expression* exp1;
	string method;
public:
	Unary(Expression* exp1, string method);
	string prettyprint();
	void unset(string var);
	int evaluate();
	void set(string var, int num);
	Unary* copy();
	~Unary();
};

#endif
