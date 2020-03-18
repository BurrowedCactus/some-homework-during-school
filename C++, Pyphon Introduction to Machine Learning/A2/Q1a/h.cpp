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
	int N = D.labels.size();
	int N1 = 0;
	int N2 = 0;
	for(const auto& label: D.labels){
		if (label == 5){
			++N1;
		} else {
			++N2;
		}
	}
	pi = 1.0 * N1 / N;

	mu1 = VectorXd::Zero(Dimen);
	mu2 = VectorXd::Zero(Dimen);

	for(int i = 0; i < N; ++i){
		if (D.labels.at(i) == 5){
			mu1 += D.coordinates.at(i);
		} else {
			mu2 += D.coordinates.at(i);
		}
	}
	mu1 /= N1;
	mu2 /= N2;

	Eigen::MatrixXd S1(Dimen,Dimen);
	Eigen::MatrixXd S2(Dimen,Dimen);
	for(int i = 0; i < N; ++i){
		if (D.labels.at(i) == 5){
			S1 += (D.coordinates.at(i) - mu1) * ((D.coordinates.at(i) - mu1).transpose());
		} else {
			S2 += (D.coordinates.at(i) - mu2) * ((D.coordinates.at(i) - mu2).transpose());
		}
	}
	S1 /= N1;
	S2 /= N2;

	sigma = 1.0 * N1 / N * S1 + 1.0 * N2 / N * S2; 

	MatrixXd INVERSE = sigma.inverse();
	w = INVERSE * (mu1 - mu2);  
	w0 = -0.5 * mu1.transpose() * INVERSE * mu1;
	w0 += 0.5 * mu2.transpose() * INVERSE * mu2;
	w0 += log(pi/(1-pi));
std::cout << "pi is: " << pi << std::endl << std::endl;
std::cout << "mu1 is: " << mu1.transpose() << std::endl << std::endl;
std::cout << "mu2 is: " << mu2.transpose() << std::endl << std::endl;
std::cout << "sigma(diagonal) is: " << sigma.diagonal().transpose() << std::endl << std::endl;
std::cout << "w is: " << w.transpose() << std::endl << std::endl;
std::cout << "w0 is: " << w0 << std::endl << std::endl;

};

int h::guess(VectorXd vec) const{
	if (1 / (1 + exp(-(w.transpose() * vec + w0))) >= 0.5){
		return 5;
	} else {
		return 6;
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
