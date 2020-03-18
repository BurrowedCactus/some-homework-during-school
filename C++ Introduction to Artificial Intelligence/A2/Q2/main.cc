#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>
#include <utility>
#include "database.h"
#include "factor.h"
using namespace std;

bool compare(const pair<double, int>& a, const pair<double, int>& b){
	return a.first <= b.first;
}

factor inference(vector<factor> list, vector<int> queryVariables, vector<int> orderedListOfHiddenVariables, map<int,int> evidenceList){
	for (auto& each : list){
		cerr << each << endl;
	}

	// This function should restrict the factors in factorList according to the evidence in evidenceList.
	for (auto it = evidenceList.begin(); it != evidenceList.end(); ++it){
		for (auto& each : list){
			each.restrict(it->first, it->second);
		}
	}

	for (auto& each : list){
		cerr << each << endl;
	}

	// it should sumout the hidden variables from the product of the factors in factorList. The products and sums should be 
	// interleaved so that each summation is done over the minimal product of factors necessary. The variables should be
	// summed out in the order given in orderedListOfHiddenVariables
	vector<factor> list2;
	for (auto& hidden : orderedListOfHiddenVariables){
		factor f;
		for (auto& fact : list){
			if (fact.contains(hidden)){
				f.multiply(fact);
			} else {
				list2.push_back(fact);
			}
		}
		f.sumout(hidden);
		list2.push_back(f);
		list = list2;
		list2.clear();
	}

	//the answer can be normalized if a probability distribution that sums up to 1 is desired.
	factor f;
	for (auto& each : list){
		f.multiply(each);
	}
	f.normalize();
	return f;
}


int main(){
	Database database("trainData.txt", "trainLabel.txt");
	ifstream myfile ("words.txt");
	vector<string> words;
	if (myfile.is_open()){
		string line;
		while ( getline (myfile,line) ){
			words.push_back(line);
		}
		myfile.close();
	} else {
		cerr << "Unable to open \"words.txt\"";
	}

	int total_num_of_words = database.MAX_FEATURE + 1;
//initialized with Laplace correction 
	vector<int> num_of_docs_ath(total_num_of_words, 1);
	vector<int> num_of_docs_gra(total_num_of_words, 1);
	int ath = 2;
	int gra = 2;

	for (auto& it : database.data){
		if (it.second == atheism){
			for (auto& it2 : it.first){
				num_of_docs_ath.at(it2) += 1;
			}
			++ath;
		} else if (it.second == graphics){
			for (auto& it2 : it.first){
				num_of_docs_gra.at(it2) += 1;
			}
			++gra;
		}		
	}

	list<pair<double,int>> discriminative;
	for (int i = 0; i < total_num_of_words; ++i){
		double ratio_ath = (0.0+num_of_docs_ath.at(i))/ath;
		double ratio_gra = (0.0+num_of_docs_gra.at(i))/gra;
		discriminative.push_back(make_pair(log(ratio_ath)-log(ratio_gra), i));
	}
	discriminative.sort(compare);

//output
	int count = 1;
	int standard[10];
	for (auto const& it : discriminative){
//add 1 since it is the line number
		standard[count-1] = it.second;
		cout << count << "th discriminative word is " << words.at(it.second + 1) << endl;
		++count;
		if (count > 10) {
			break;
		}
	}


	factor theta_c(vector<int>({total_num_of_words + 1}), vector<double>({1.0*ath/(ath+gra), 1.0*gra/(ath+gra)}));

	vector<factor> theta_ath(num_of_docs_ath.size());
	vector<factor> theta_gra(num_of_docs_gra.size());

	for (int i = 0; i < total_num_of_words; ++i){
		double ratio = num_of_docs_ath[i]/ath;
		theta_ath[i].multiply(factor(vector<int>({i}), vector<double>({ratio, 1 - ratio})));
	}
	
	for (int i = 0; i < total_num_of_words; ++i){
		double ratio = num_of_docs_gra[i]/gra;
		theta_gra[i].multiply(factor(vector<int>({i}), vector<double>({ratio, 1 - ratio})));
	}
	vector<int> queryVariables({total_num_of_words + 1});
	vector<int> orderedListOfHiddenVariables(total_num_of_words);
	generate(orderedListOfHiddenVariables.begin(), orderedListOfHiddenVariables.end(), [n = 0] () mutable { return n++; });
	map<int,int> evidenceList;
	
	int right = 0;
	int wrong = 0;
	for (auto& it : database.data){
		for (int i = 0; i < 10; ++i){
			if (it.first.count(standard[i]) == 1){
				evidenceList.insert(pair<int,int>(standard[i],1));
			} else {
				evidenceList.insert(pair<int,int>(standard[i],-1));
			}
		}
		factor answer = inference(theta_ath, queryVariables, orderedListOfHiddenVariables, evidenceList);
		if ((answer.result() >= 0.5 && it.second == atheism) || (answer.result() < 0.5 && it.second == graphics)){
			++right;
		} else {
			++wrong;
		}
	}
	cout << "prediction rate on training data is: " << 1.0*right/(right + wrong) << endl;



}