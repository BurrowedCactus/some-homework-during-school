#include <string>
#include <iostream>
#include "Expression.h"
#include "Unary.h"

using namespace std;

Unary::Unary(Expression* exp1, string method): exp1{exp1}, method{method}{}

string Unary::prettyprint(){
	if (method == "NEG"){
		return "-" + exp1->prettyprint();
	} else {
		return "|" + exp1->prettyprint() + "|";
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

Unary* Unary::copy(){
	return new Unary{exp1->copy(), method};
}

Unary::~Unary(){
	delete exp1;
}
