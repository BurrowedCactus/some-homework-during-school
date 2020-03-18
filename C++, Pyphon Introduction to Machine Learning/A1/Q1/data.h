#ifndef _DATA_H
#define _DATA_H

#include <string>
#include <vector>
#include <utility>

struct X{
	std::vector<int> x;

	void add(int a){
		x.push_back(a);
	}
	double dist(const X other) const;
};

struct data{
	std::vector<std::pair<X,int>> content;

	data();
	//initialize an empty data, like the default constructor.
	//this is to fix a bug that compiler mix up "h" and "h()".
	data(int a);
	data(std::string features, std::string labels);
	void add(const data other);
};

#endif
