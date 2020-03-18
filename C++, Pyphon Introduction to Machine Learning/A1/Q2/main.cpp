#include <string>
#include <iostream>
#include "data.h"
#include "h.h"

const static double lambda = 4;
const static int FOLD = 10;
int main(){
	data* data_set = new data[FOLD];
	for (int i = 1; i <= 10; ++i){
		std::string s1("trainInput" + std::to_string(i) + ".csv");
		std::string s2("trainTarget" + std::to_string(i) + ".csv");
		data_set[i-1] = data(s1, s2);
	}

	data test_data("testInput.csv", "testTarget.csv");
	double min_error = 100000000;
	int best_k = 0;
	h best_h(0);
	h temp_h(0);
	for(double k = 0; k <= lambda + 0.1; k = k + 0.1){
		double error = 0;
		for (int i = 0; i < FOLD ; ++i){
			data learn;
			for (int l = 0; l < FOLD; ++l){
				if (l != i){
					learn.add(data_set[l]); 
				}
			}
			h hypothesis(k, learn);
			temp_h = hypothesis;
			error += hypothesis.loss(data_set[i]);  
		}
		error /= FOLD;
std::cout << "when labmda is " << k << ", the accuracy is " << error << std::endl;
		if (min_error > error ){
			best_k = k;
			best_h = temp_h;
			min_error = error;
		} 
	}
	double test_error = best_h.loss(test_data);
std::cout << "the best labmda is " << best_k << std::endl;
std::cout << "the test error is " << test_error<< std::endl;
	delete[] data_set;
}
