#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>

#include "data.h"
#include <Eigen/Dense>

using namespace std;

data::data(){}

void data::add(const data& other){
	coordinates.insert(coordinates.end(), other.coordinates.begin(), other.coordinates.end());
	labels.insert(labels.end(), other.labels.begin(), other.labels.end());
}

data::data(string input, string target){
    	ifstream in1(input);
	ifstream in2(target);
	string line;
	
	while(getline(in1,line)){
		vector<int> temp;
		temp.push_back(1);
		while (line.find(",") != string::npos){
			istringstream line_stream(line);
			int x;
			line_stream >> x;
			temp.push_back(x);
			line = line.substr(line.find(",") + 1);
		}
		istringstream line_stream(line);
		int x;
		line_stream >> x;
		temp.push_back(x);

		Eigen::VectorXd vec(temp.size());
		for(uint i = 0; i < temp.size(); ++i){
			vec(i) = temp.at(i);
		}
		coordinates.push_back(vec);

		//label
		int label;
		in2 >> label;
		//setup
		if (label == 5){
			labels.push_back(1);
		} else {
			labels.push_back(-1);
		}
	}
}

