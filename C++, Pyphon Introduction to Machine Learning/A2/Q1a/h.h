#ifndef _H_H
#define _H_H
#include <Eigen/Dense>
#include "data.h"

class h{
	double pi;
	Eigen::VectorXd mu1;
	Eigen::VectorXd mu2;
	Eigen::MatrixXd sigma;
	Eigen::VectorXd w;
	double w0;
public:
	h(const data& D);
	
	//given a coordinate, predict its label.
	int guess(Eigen::VectorXd vec) const;

	//given a set of coordinates and its labels, output the propability that it guesses wrongly.
	double loss(const data& D) const;
};

#endif