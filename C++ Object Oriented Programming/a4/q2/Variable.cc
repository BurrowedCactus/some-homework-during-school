#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Expression.h"
#include "Variable.h"

using namespace std;

Variable::Variable(int value, string name, bool isSet): 
		value{value}, name{name}, isSet{isSet}{}


string Variable::prettyprint(){
	if (isSet){
		ostringstream oss;
		oss << value;
		return oss.str();
	} else {
		return name;
	}
}

void Variable::unset(string var){
	isSet = false;
}

int Variable::evaluate(){
	if (isSet){
		return value;
	} else {
		throw name;
	}
}

void Variable::set(string var, int num){
	if (var == name){
		isSet = true;
		value = num;
	}
}

Variable* Variable::copy(){
	return new Variable{value, name, isSet};
}
