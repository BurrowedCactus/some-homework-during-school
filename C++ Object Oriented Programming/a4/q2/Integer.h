#ifndef	INTEGER_H
#define INTEGER_H

#include <string>
#include <iostream>
#include "Expression.h"

using namespace std;

class Integer : public Expression{
	int value;
public:
	Integer(int value);
	string prettyprint();
	void unset(string var);
	int evaluate();
	void set(string var, int num);
	Integer* copy();
};
#endif
