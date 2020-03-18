#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
using namespace std;

class Expression{
public:
	virtual void prettyprint()=0;
	virtual void unset(string var)=0;
	virtual int evaluate()=0;
	virtual void set(string var, int num)=0;
	virtual ~Expression();
};
#endif
