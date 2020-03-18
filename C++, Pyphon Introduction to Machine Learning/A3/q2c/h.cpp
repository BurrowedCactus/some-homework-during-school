#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <Eigen/Dense>

#include "h.h"
#include "data.h"
using namespace Eigen;

double kernal (VectorXd x, VectorXd y, int d){
//	return x.transpose() * y;
//	return exp(- (x - y).squaredNorm() / (2 * d * d));
	return pow(x.transpose() * y + 1, d);
}


h::h(int d, const data& D): d{d} , D{D} {
	int N = D.coordinates.size();

	y = VectorXd(N);
	for (int i = 0; i < N; ++i){
		y(i) = D.targets.at(i);
	}

	MatrixXd gram(N,N);
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			gram(j,i) = kernal(D.coordinates.at(i), D.coordinates.at(j), d);
		}
	}
	right = (gram + MatrixXd::Identity(N,N)).inverse() * y;


};

double h::guess(VectorXd vec) const{
	MatrixXd temp(1, D.coordinates.size());
	for (uint i = 0; i < D.coordinates.size(); ++i){
		temp(0, i) = kernal(vec, D.coordinates.at(i), d);
	}
	return (temp * right)(0,0);
}

double h::loss(const data& D) const{
	double square_error = 0;
	for(uint i = 0; i < D.coordinates.size(); ++i){
		double prediction = guess(D.coordinates.at(i));
		square_error += (prediction - D.targets.at(i))*(prediction - D.targets.at(i));
	}
	return square_error / D.coordinates.size();
}
