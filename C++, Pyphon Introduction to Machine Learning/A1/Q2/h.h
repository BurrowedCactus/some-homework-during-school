#ifndef _H_H
#define _H_H
#include <Eigen/Dense>
#include "data.h"

class h{
	Eigen::Vector3d w;
	double lambda;
	data d; 
public:

	h();
	//initialize an empty h, like the default constructor.
	//this is to fix a bug that compiler mix up "h" and "h()".
	h(int a);

	h(double lambda, const data& other);
	
	double loss(const data& other) const;
};

#endif