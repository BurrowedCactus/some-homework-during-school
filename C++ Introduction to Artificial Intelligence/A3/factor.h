#ifndef FACTOR_H_
#define FACTOR_H_
#include <ostream>
#include <vector>
#include <map>
#include <set>

struct Values{
  enum Feature {
    Forms = 0,
		Symptoms = 1,
		Gene = 2
  };

  enum Value {
    healthy = 0,
		mild,
		severe,

		sloepnea = 10,
		foriennditis,
		degar_spots,

		special = 20,
		normal
  };
  Value my_value;
  std::vector<Value> kinds(Feature fea);
};

class factor{
  std::set<Values::Feature> features;
	std::map<std::set<Values>, double> table;

	void add(factor other);

public:
	factor(){}
	factor(std::vector<Values::Feature>, std::vector<double>);

	unsigned int size(){
		return table.size();
	}
	double result();
	bool contains(Values::Feature fea);
	void restrict(Values::Feature fea, Values v);
	void multiply(factor other);
	void sumout(Values::Feature fea);
	void normalize();
	friend std::ostream& operator<<(std::ostream& os, const factor& fact);
};


#endif   // FACTOR_H_
