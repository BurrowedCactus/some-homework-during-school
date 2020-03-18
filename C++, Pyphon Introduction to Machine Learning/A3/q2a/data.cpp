#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>
#include "data.h"
#include <Eigen/Dense>

using namespace std;

data::data(){}

void data::add(const data& other){
	coordinates.insert(coordinates.end(), other.coordinates.begin(), other.coordinates.end());
	targets.insert(targets.end(), other.targets.begin(), other.targets.end());
}

data::data(string input, string target){
    	ifstream in1(input);
	ifstream in2(target);
	string line;
	
	while(getline(in1,line)){
		vector<double> temp;
		while (line.find(",") != string::npos){
			istringstream line_stream(line);
			int x;
			line_stream >> x;
			temp.push_back(x);
			line = line.substr(line.find(",") + 1);
		}
		istringstream line_stream(line);
		double x;
		line_stream >> x;
		temp.push_back(x);

		Eigen::VectorXd vec(temp.size());
		for(uint i = 0; i < temp.size(); ++i){
			vec(i) = temp.at(i);
//cerr << temp.at(i) << " ";
		}
		coordinates.push_back(vec);
//cerr <<  " with the target ";
		//label
		double label_number;
		in2 >> label_number;
//cerr << label_number << endl;
		targets.push_back(label_number);
	}
}

