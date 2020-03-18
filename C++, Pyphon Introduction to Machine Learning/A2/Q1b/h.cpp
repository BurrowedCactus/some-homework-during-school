#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <Eigen/Dense>

#include "h.h"
#include "data.h"
using namespace Eigen;

double sigmoid(double a){
	return 1.0 / (1.0 + exp(-a)); 
}

h::h(double lambda, const data& D): lambda{lambda}{
	int Dimen = D.coordinates.at(0).size();
	int N = D.coordinates.size();

	MatrixXd X(Dimen, N);
	for(int i = 0; i < N; ++i){
		X.col(i) = D.coordinates.at(i);
	}

	w = VectorXd::Random(Dimen);
	w /= 100;
	for(int i = 0; i < 10; ++i){
		MatrixXd R = MatrixXd::Zero(N,N);
		for(int i = 0; i < N; ++i){
			R(i,i) = sigmoid(w.transpose() * X.col(i)) * (1 - sigmoid(w.transpose() * X.col(i)));
		}

		MatrixXd H = X * R * X.transpose() + lambda * MatrixXd::Identity(Dimen,Dimen);	
		VectorXd gradient = VectorXd::Zero(Dimen);
		for(int i = 0; i < N; ++i){
			gradient.noalias() += (sigmoid(w.transpose() * D.coordinates.at(i)) - D.labels.at(i)) * D.coordinates.at(i);
		}
		gradient.noalias() += lambda * w;	
		w.noalias() -= H.inverse() * gradient;
	}

};

int h::guess(VectorXd vec) const{
	if ((- w.transpose()) * vec >= 0){
		return 0;
	} else {
		return 1;
	}
}

double h::loss(const data& D) const{
	int total = 0;
	int right = 0;
	auto it = D.labels.begin();
	for(const auto& coords: D.coordinates){
		if (guess(coords) == *it){
			++right;
		}
		++it;
		++total;
	}
	return 1 - 1.0 * right / total;
}
