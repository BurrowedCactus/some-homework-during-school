#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <utility>
#include <fstream>

#include "data.h"
using namespace std;

double X::dist(const X other) const {
	auto it1 = x.begin();
	auto it2 = other.x.begin();
	double sum = 0;
	for( ; (it1 != x.end() && it2 != other.x.end()); ++it1, ++it2){
		sum += pow(*it1 - *it2, 2);
	}
	return sqrt(sum);
}

data::data(){

}
data::data(int a){
	
}

void data::add(const data other){
	content.insert(content.end(), other.content.begin(), other.content.end());
}

data::data(string train_data, string train_label){
    	ifstream in1(train_data);
	ifstream in2(train_label);
	string line;
	while(getline(in1,line)){
		//features
		stringstream lineStream(line);
		string cell;
		X features;
		while(std::getline(lineStream,cell,',')){
			istringstream number(cell);
			int x;
			number >> x;
			features.add(x);
		}

		//label
		int label;
		in2 >> label;
		//setup
		content.push_back(make_pair(features,label));
	}
}