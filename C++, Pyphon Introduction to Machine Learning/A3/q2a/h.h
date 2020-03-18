#ifndef _H_H
#define _H_H
#include <Eigen/Dense>
#include "data.h"

class h{
	int d;
	Eigen::VectorXd w;
public:
	h(int d, const data& D);
	
	//given a set of coordinates and its labels, output the propability that it guesses wrongly.
	double loss(const data& D) const;
};

#endif