#include <string>
#include <iostream>
#include "Expression.h"
#include "Binary.h"

using namespace std;

Binary::Binary(Expression* exp1, Expression* exp2, string method):
		exp1{exp1}, exp2{exp2}, method{method}{}

void Binary::prettyprint(){
	cout << '(';
	exp1->prettyprint();
	cout << ' ' << method << ' ';
	exp2->prettyprint();
	cout << ')';
}

void Binary::unset(string var){
	exp1->unset(var);
	exp2->unset(var);
}

int Binary::evaluate(){
	if (method == "+"){
		return exp1->evaluate() + exp2->evaluate();
	} else if (method == "-"){
		return exp1->evaluate() - exp2->evaluate();
	} else if (method == "*"){
		return exp1->evaluate() * exp2->evaluate();
	} else {
		return exp1->evaluate() / exp2->evaluate();
	}
}

void Binary::set(string var, int num){
	exp1->set(var, num);
	exp2->set(var, num);
}

Binary::~Binary(){
	delete exp1;
	delete exp2;
}
