#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>

#include "data.h"
#include <Eigen/Dense>

using namespace std;


data::data(){

}
data::data(int a){
	
}

void data::add(const data& other){
	coordinates.insert(coordinates.end(), other.coordinates.begin(), other.coordinates.end());
	targets.insert(targets.end(), other.targets.begin(), other.targets.end());
}

data::data(string input, string target){
    	ifstream in1(input);
	ifstream in2(target);
	string line;
	while(getline(in1,line)){
		istringstream line_stream(line);
		double x;
		line_stream >> x;
		istringstream line_stream2(line.substr(line.find(",") + 1));
		double y;
		line_stream2 >> y;
		coordinates.push_back(Eigen::Vector3d(1,x,y));
		double t;
		in2 >> t;
		targets.push_back(t);
	}
}

