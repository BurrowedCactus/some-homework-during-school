#include <string>
#include <iostream>
#include "data.h"
#include "h.h"

const static int K = 30;
const static int FOLD = 10;
int main(){
	data* data_set = new data[FOLD];
	for (int i = 1; i <= 10; ++i){
		std::string s1("trainData" + std::to_string(i) + ".csv");
		std::string s2("trainLabels" + std::to_string(i) + ".csv");
		data_set[i-1] = data(s1, s2);
	}

	data test_data("testData.csv", "testLabels.csv");
	double max_accuracy = 0;
	int best_k = 0;
	h best_h(0);
	h temp_h(0);
	for(int k = 1; k <= K; ++k){
		double accuracy = 0;
		for (int i = 0; i < FOLD ; ++i){
			data learn(0);
			for (int l = 0; l < FOLD; ++l){
				if (l != i){
					learn.add(data_set[l]); 
				}
			}
			h hypothesis(k, learn);
			temp_h = hypothesis;
			accuracy += hypothesis.test(data_set[i]);  
		}
		accuracy /= FOLD;

std::cout << "when k is " << k << ", the accuracy is " << accuracy  << std::endl;
		if (max_accuracy < accuracy){
			best_k = k;
			best_h = temp_h;
			max_accuracy = accuracy;
		} 
	}
	double test_accuracy = best_h.test(test_data);
std::cout << "the best k is " << best_k << std::endl;
std::cout << "the test accuracy is " << test_accuracy << std::endl;
	delete[] data_set;
}