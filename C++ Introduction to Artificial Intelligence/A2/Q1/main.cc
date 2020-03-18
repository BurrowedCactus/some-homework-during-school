#include <iostream>
#include <vector>
#include "factor.h"
using namespace std;

string translate(int i){
	switch(i){
		case 1:
			return "Trav";
		case 2:
			return "FP";
		case 3:
			return "Fraud";
		case 4:
			return "IP";
		case 5:
			return "OC";
		case 6:
			return "CRP";
		default:
			return "";
	}
} 


factor inference(vector<factor> list, vector<int> queryVariables, vector<int> orderedListOfHiddenVariables, map<int,int> evidenceList){
	cerr << " starting inference, check input factors" << endl;
	for (auto& each : list){
		cerr << each << endl;
	}
	cerr << " initial condition check end" << endl;

	// This function should restrict the factors in factorList according to the evidence in evidenceList.
	for (auto it = evidenceList.begin(); it != evidenceList.end(); ++it){
		for (auto& each : list){
			each.restrict(it->first, it->second);
		}
	}

	cerr << "after initial restriction we have" << endl;	
	for (auto& each : list){
		cerr << each << endl;
	}
	cerr << "initial restriction complete." << endl;

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
cerr << "after suming out factors contain " << translate(hidden) << ", left factors are: "<< endl;
	for (auto& each : list){
                cerr << each << endl;
        }
cerr << "sum out factors contain " << translate(hidden) << " end." << endl;
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
	vector<factor> list;
	factor a(vector<int>({5}), vector<double>({0.6,0.4}));
	factor b(vector<int>({5,6}), vector<double>({0.1,0.9,0.001,0.999}));
	factor c(vector<int>({1,3}), vector<double>({0.01,0.99,0.004,0.996}));
	factor d(vector<int>({1}), vector<double>({0.05,0.95}));
	factor e(vector<int>({1,3,2}), vector<double>({0.9,0.1,0.9,0.1,0.1,0.9,0.01,0.99}));
	factor f(vector<int>({5,3,4}), vector<double>({0.02,0.98,0.01,0.99,0.011,0.989,0.001,0.999}));
	list.push_back(a);
	list.push_back(b);
	list.push_back(c);
	list.push_back(d);
	list.push_back(e);
	list.push_back(f);

	vector<int> queryVariables({3});
	vector<int> orderedListOfHiddenVariables({1,2,4,5,6});
	map<int,int> evidenceList;

	factor x = inference(list,queryVariables,orderedListOfHiddenVariables,evidenceList);
cerr << "answer is " << endl;
	cerr << x << endl;
	
	evidenceList.insert(pair<int,int>(2,1));
	evidenceList.insert(pair<int,int>(4,-1));
	evidenceList.insert(pair<int,int>(6,1));
	factor y = inference(list,queryVariables,orderedListOfHiddenVariables,evidenceList);
cerr << "the new answer is " << endl;
	cerr << y << endl;

	evidenceList.insert(pair<int,int>(1,1));
	factor z = inference(list,queryVariables,orderedListOfHiddenVariables,evidenceList);
cerr << "the new answer is " << endl;
	cerr << z << endl;

	map<int,int> evidenceList2;
	evidenceList2.insert(pair<int,int>(4,1));
	factor m = inference(list,queryVariables,orderedListOfHiddenVariables,evidenceList2);
cerr << "before:" << endl;
	cerr << m << endl;

	evidenceList2.insert(pair<int,int>(6,1));
	factor n = inference(list,queryVariables,orderedListOfHiddenVariables,evidenceList2);
cerr << "after:" << endl;
	cerr << n << endl;
	
}
