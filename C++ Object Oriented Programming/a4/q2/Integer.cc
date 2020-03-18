#include "Expression.h"
#include "Integer.h"
#include <sstream>
#include <string>

using namespace std;

Integer::Integer(int value): value{value}{}

string Integer::prettyprint(){
	ostringstream oss;
	oss << value;
	return oss.str();
}

void Integer::unset(string var){}

int Integer::evaluate(){
	return value;
}

void Integer::set(string var, int num){}

Integer* Integer::copy(){
	return new Integer{value};
}
