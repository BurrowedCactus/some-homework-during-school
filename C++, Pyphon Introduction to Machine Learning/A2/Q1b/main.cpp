#include <string>
#include <iostream>
#include "data.h"
#include "h.h"

const double LAMBDA = 20000;
const int FOLD = 10; 

int main(){
	data* train_set = new data[FOLD];
	for (int i = 1; i <= FOLD; ++i){
		std::string s1("trainData" + std::to_string(i) + ".csv");
		std::string s2("trainLabels" + std::to_string(i) + ".csv");
		train_set[i-1].add(data(s1, s2));
	}
	data test_data("testData.csv", "testLabels.csv");

	double best_accuracy = 0;
	double best_lambda = 0;
	
	for(double lambda = 0; lambda <= LAMBDA; lambda += 500){
		double accuracy = 0;
		for (int i = 0; i < FOLD ; ++i){
			data learn;
			for (int l = 0; l < FOLD; ++l){
				if (l != i){
					learn.add(train_set[l]); 
				}
			}
			h hypothesis(lambda, learn);
			accuracy += (1 - hypothesis.loss(train_set[i]));  
		}
		accuracy /= FOLD;
std::cout << "when labmda is " << lambda << ", the accuracy is " << accuracy << std::endl;
		if (best_accuracy < accuracy){
			best_lambda = lambda;
			best_accuracy = accuracy;
		} 
	}

	data all;
	for (int i = 0; i < FOLD; ++i){
		all.add(train_set[i]); 
	}
	h best_h(best_lambda, all);
	double test_accuracy = 1 - best_h.loss(test_data);
std::cout << "the best labmda is " << best_lambda  << std::endl;
std::cout << "the test accuracy is " << test_accuracy << std::endl;
	delete[] train_set;
}