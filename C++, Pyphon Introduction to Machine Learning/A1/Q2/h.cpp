#include <vector>
#include <map>
#include <cmath>
#include <Eigen/Dense>

#include "h.h"
#include "data.h"
using namespace Eigen;

h::h(){

}
h::h(int a){

}
h::h(double lambda, const data& other):lambda{lambda}, d{other}{

	Matrix3d A = Matrix3d::Zero();
	Vector3d b(0,0,0);
	auto it = other.targets.begin();
	for(const auto coords: other.coordinates){
		A += coords * coords.transpose();
		b += (*it) * coords;
		++it;
	}
	A += lambda * Matrix3d::Identity();
	w = A.inverse() * b;
};


double h::loss(const data& other) const{
	double answer = 0;
	auto it = other.targets.begin();
	for(const auto coords: other.coordinates){
		double vertical_distance = (*it) - w.transpose() * coords;
		answer += pow(vertical_distance,2);
		++it;
	}
	return 0.5 * answer + 0.5 * lambda * w.squaredNorm();
	return 0;
}
