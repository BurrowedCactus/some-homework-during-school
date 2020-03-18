#include <string>
#include <iostream>
#include "data.h"
#include "h.h"

const static int FOLD = 10;

int main(){
	data* train_set = new data[FOLD];
	for (int i = 1; i <= FOLD; ++i){
		std::string s1("trainInput" + std::to_string(i) + ".csv");
		std::string s2("trainTarget" + std::to_string(i) + ".csv");
		train_set[i-1].add(data(s1, s2));
	}
	data test_data("testInput.csv", "testTarget.csv");

	double best_error = 10000000;
	int best_d = 0;
	clock_t t;

	for(int d = 1; d <= 4; ++d){
		t = clock();
		double error = 0;
		for (int i = 0; i < FOLD ; ++i){
			data learn;
			for (int l = 0; l < FOLD; ++l){
				if (l != i){
					learn.add(train_set[l]); 
				}
			}
			h hypothesis(d, learn);
			error += hypothesis.loss(train_set[i]);
		}
		error /= FOLD;
		if (best_error > error){
			best_d = d;
			best_error = error;
		}
		t = clock() - t;
std::cout << "when d is " << d << ", the error is " << error;
std::cout << ", the training takes " << (0.0+t)/CLOCKS_PER_SEC << " seconds."<<std::endl;

	}

	data all;
	for (int i = 0; i < FOLD; ++i){
		all.add(train_set[i]); 
	}
	h best_h(best_d, all);
	double test_error = best_h.loss(test_data);
std::cout << "the best d is " << best_d  << std::endl;
std::cout << "the test error is " << test_error << std::endl;
	delete[] train_set;
}