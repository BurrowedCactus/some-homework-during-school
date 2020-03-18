#include "Expression.h"
#include "Integer.h"

using namespace std;

Integer::Integer(int value): value{value}{}

void Integer::prettyprint(){
	cout << value;
}

void Integer::unset(string var){}

int Integer::evaluate(){
	return value;
}

void Integer::set(string var, int num){}
