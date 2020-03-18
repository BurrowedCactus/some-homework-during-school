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

h::h(int d, const data& D): d{d}{
	std::vector<Eigen::VectorXd> new_coords;
	for(auto& coord : D.coordinates){
		new_coords.push_back(transform(d,coord));
	}

	int Dimen = new_coords.at(0).size();

	MatrixXd A = MatrixXd::Zero(Dimen,Dimen);
	VectorXd b = VectorXd::Zero(Dimen);
	auto it = D.targets.begin();

	for(const auto coords: new_coords){
		A += coords * coords.transpose();
		b += (*it) * coords;
		++it;
	}
	A += MatrixXd::Identity(Dimen,Dimen);
	w = A.inverse() * b;
};

double h::loss(const data& other) const{
	double answer = 0;
	auto it = other.targets.begin();
	for(const auto coords: other.coordinates){
		double vertical_distance = (*it) - w.transpose().dot(transform(d,coords));
		answer += pow(vertical_distance,2);
		++it;
	}
	return answer / other.targets.size() ;
}

