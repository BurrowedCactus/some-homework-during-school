#ifndef _DATA_H
#define _DATA_H

#include <string>
#include <vector>
#include <utility>
#include <Eigen/Dense>



struct data{
	data();
	std::vector<Eigen::VectorXd> coordinates;
	std::vector<int> labels;

	data(int a);
	data(std::string input, std::string target);
	void add(const data& other);
};

#endif
