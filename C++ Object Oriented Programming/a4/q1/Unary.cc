#include <string>
#include <iostream>
#include "Expression.h"
#include "Unary.h"

using namespace std;

Unary::Unary(Expression* exp1, string method): exp1{exp1}, method{method}{}

void Unary::prettyprint(){
	if (method == "NEG"){
		cout << '-';
		exp1->prettyprint();
	} else if (method == "ABS"){
		cout << '|';
		exp1->prettyprint();
		cout << '|';
	}
}

void Unary::unset(string var){
	exp1->unset(var);
}

int Unary::evaluate(){
	if (method == "NEG"){
		return - exp1->evaluate();
	} else {
		int temp = exp1->evaluate();
		return (temp >= 0)? temp : - temp;
	} 
}

void Unary::set(string var, int num){
	exp1->set(var, num);
}

Unary::~Unary(){
	delete exp1;
}
