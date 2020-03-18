#ifndef _H_H
#define _H_H
#include <Eigen/Dense>
#include <vector>
#include "data.h"

class h{
	int d;
	Eigen::MatrixXd right;
	Eigen::VectorXd y;
	data D;
public:
	h(int d, const data& D);

	double guess(Eigen::VectorXd) const;
	//given a set of coordinates and its labels, output the propability that it guesses wrongly.
	double loss(const data& D) const;
};

#endif