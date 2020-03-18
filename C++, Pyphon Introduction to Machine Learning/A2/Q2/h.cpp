#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <Eigen/Dense>

#include "h.h"
#include "data.h"
using namespace Eigen;

h::h(const data& D){
	int Dimen = D.coordinates.at(0).size();
	int N = D.coordinates.size();

	w = VectorXd::Random(Dimen);
	while(true){
		bool changed = false;
		int count = 0;
		for(int i = 0; i < N; ++i){
			if (D.labels.at(i) * w.transpose() * D.coordinates.at(i) > 0){
				
			} else {
				changed = true;
				++count;
				w.noalias() += D.labels.at(i) * D.coordinates.at(i);
			}
		}
		if (changed){
			std::cerr << "Weight is changed " << count << " times."<< std::endl;
		} else {
			std::cerr << "converged." << std::endl;
			break;
		}
	}
};

int h::guess(VectorXd vec) const{
	if (1 / (1 + exp(-(w.transpose().dot(vec)))) >= 0.5){
		return 1;
	} else {
		return -1;
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
