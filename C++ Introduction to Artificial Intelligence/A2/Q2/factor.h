#ifndef FACTOR_H_
#define FACTOR_H_
#include <ostream>
#include <vector>
#include <map>
#include <set>

class factor{
	std::map<std::set<int>, double> table;
public:
	factor(){}
	factor(std::vector<int>variables, std::vector<double> values);

	double result();
	bool contains(int var);
	void restrict(int var, int val);
	void multiply(factor other);
	void sumout(int var);
	void normalize();
	friend std::ostream& operator<<(std::ostream& os, const factor& fact);
};

#endif   // FACTOR_H_