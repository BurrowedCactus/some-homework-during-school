#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <Eigen/Dense>

#include "h.h"
#include "data.h"
using namespace Eigen;

Eigen::VectorXd transform(int d, Eigen::VectorXd vec){
	switch(d){
		case 1:{
				Eigen::VectorXd answer(3);
				answer << 1, vec(0), vec(1); 
				return answer;
			}
		case 2:{
				Eigen::VectorXd answer(6);
				answer << 1, vec(0), vec(1), vec(0)*vec(0), vec(0)*vec(1), vec(1)*vec(1);
				return answer;
				break;
			}
		case 3:{
				Eigen::VectorXd answer(10);
				answer << 1, vec(0), vec(1), vec(0)*vec(0), vec(0)*vec(1), vec(1)*vec(1), vec(0)*vec(0)*vec(0),
				          vec(0)*vec(0)*vec(1), vec(0)*vec(1)*vec(1), vec(1)*vec(1)*vec(1);
				return answer;
				break;
			}
		default:{
				Eigen::VectorXd answer(15);
				answer << 1, vec(0), vec(1), vec(0)*vec(0), vec(0)*vec(1), vec(1)*vec(1), 
				          vec(0)*vec(0)*vec(0), vec(0)*vec(0)*vec(1), vec(0)*vec(1)*vec(1), vec(1)*vec(1)*vec(1), 
				          vec(0)*vec(0)*vec(0)*vec(0), vec(0)*vec(0)*vec(0)*vec(1), vec(0)*vec(0)*vec(1)*vec(1), 
				          vec(0)*vec(1)*vec(1)*vec(1), vec(1)*vec(1)*vec(1)*vec(1);
				return answer;
			}
	}
}


h::h(int d, const data& D): d{d} {

	int Dimen = transform(d,D.coordinates.at(0)).size();
	int N = D.coordinates.size();
	new_coords = MatrixXd(Dimen, N);

	int i = 0;
	for(auto& coord : D.coordinates){
		new_coords.col(i) = transform(d,coord);
		++i;
	}

	y = VectorXd(N);
	for (int i = 0; i < N; ++i){
		y(i) = D.targets.at(i);
	}


	MatrixXd A = new_coords * new_coords.transpose() + MatrixXd::Identity(Dimen, Dimen).inverse();

	A_inver = A.inverse();

};

double h::guess(VectorXd vec) const{
	return transform(d, vec).transpose() * A_inver * new_coords * y;
}

double h::loss(const data& D) const{
	double square_error = 0;
	for(uint i = 0; i < D.coordinates.size(); ++i){
		double prediction = guess(D.coordinates.at(i));
		square_error += (prediction - D.targets.at(i))*(prediction - D.targets.at(i));
	}
	return square_error / D.coordinates.size();
}
