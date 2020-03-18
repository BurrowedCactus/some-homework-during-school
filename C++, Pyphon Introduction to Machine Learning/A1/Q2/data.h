#ifndef _DATA_H
#define _DATA_H

#include <string>
#include <vector>
#include <utility>
#include <Eigen/Dense>



struct data{
	std::vector<Eigen::Vector3d> coordinates;
	std::vector<double> targets;

	data();
	//initialize an empty data, like the default constructor.
	//this is to fix a bug that compiler mix up "data" and "data()".
	data(int a);
	data(std::string input, std::string target);
	void add(const data& other);
};

#endif
