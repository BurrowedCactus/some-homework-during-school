#include <string>
#include <iostream>
#include "data.h"
#include "h.h"

int main(){
	data train_set;
	for (int i = 1; i <= 10; ++i){
		std::string s1("trainData" + std::to_string(i) + ".csv");
		std::string s2("trainLabels" + std::to_string(i) + ".csv");
		train_set.add(data(s1, s2));
	}
	data test_data("testData.csv", "testLabels.csv");

	h hypothesis(train_set);
	std::cout << "the accuracy on the test set is : " << 1 - hypothesis.loss(test_data) << std::endl;
}
