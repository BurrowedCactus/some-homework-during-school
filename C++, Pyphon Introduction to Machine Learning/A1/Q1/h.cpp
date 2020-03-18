#include <vector>
#include <map>
#include <cstdlib>
#include "h.h"
#include "data.h"

h::h(){

}
h::h(int a){
	
}



// find the first, second, ..., kth nearest point, take votes among these points and
// output the post popular label.
// could use a min heap, but now just use an map for simplicity.
int h::test(X x){
	std::map<double, int> ranking;
	srand (27480);
	for(auto it = d.content.begin(); it != d.content.end(); ++it){
		double temp = it->first.dist(x);
		ranking.insert(std::make_pair(temp,it->second));
	}
	
	//count votes
	auto it = ranking.begin();
	int five = 0;
	int six = 0;
	for (int i = 0; i < k; ++i){
		if (it->second == 5){
			++five;
		} else {
			++six;
		}
		++it;
	}
	if (five < six){
		return 6;
	} else if (five > six){
		return 5;
	} else if (rand() % 2 == 0){
		return 6;
	} else {
		return 5;
	}
}

double h::test(data other){
	int right = 0;
	int wrong = 0;
	for(const auto& line : other.content){
		if (line.second == test(line.first)){
			++right;
		} else {
			++wrong;
		}
	}
	if (right + wrong == 0) {
		return 1;
	} else {
		return (0.0 + right) / (right + wrong); 
	}
}
