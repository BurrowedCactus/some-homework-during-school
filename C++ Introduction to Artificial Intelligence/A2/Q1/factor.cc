#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include <set>
#include "factor.h"
using namespace std;

factor::factor(vector<int> variables, vector<double> values){
	int size = variables.size();
	int SIZE = exp2 (size);
	set<int>* array = new set<int>[SIZE];
	for (int i = 0; i < SIZE; ++i){
		for (int j = 0; j < size; ++j){
			if (((int)(i / exp2 ( size - 1 - j)) % 2) == 0) {
				array[i].insert(variables.at(j)); 
			} else {
				array[i].insert(-variables.at(j));
			}
		}
	}
	for (int i = 0; i < SIZE; ++i){
		table.insert(pair<set<int>,double>(array[i],values.at(i)));
	}
	delete[] array;
}

bool factor::contains(int var){
	if (table.size() == 0) {
		return false;
	}
	for (auto num : (table.begin())->first) {
		if (num == var || num == -var){
			return true;
		}
	}
	return false;
}

void factor::restrict(int var, int val){
	factor answer;
	bool exists = false;
	for (auto it = table.begin(); it != table.end(); ++it) {
		if((it->first).count(var*val) == 1){
			exists = true;
			set<int> temp = it->first;
			temp.erase(temp.find(var*val));
			answer.table.insert(pair<set<int>,double>(temp,it->second));
		}
	}
	if (exists){
		*this = answer;
	}
}

void factor::multiply(factor other){
	factor answer;
	if(table.size() == 0){
		*this = other;
		return;
	} else if (other.table.size() == 0){
		return;
	}
	unsigned int min_size = ((table.begin())->first).size() + ((other.table.begin())->first).size();
	for (auto it1 = table.begin(); it1 != table.end(); ++it1) {
		for (auto it2 = other.table.begin(); it2 != other.table.end(); ++it2) {
			set<int> temp;
			set_union(begin(it1->first), end(it1->first), 
			          begin(it2->first), end(it2->first), inserter(temp, begin(temp)));
			min_size = fmin(temp.size(), min_size);
			answer.table.insert(pair<set<int>, double>(temp, it1->second * it2->second));		
		}
			
	}
	factor answer2;
	for (auto it = answer.table.begin(); it != answer.table.end(); ++it) {
		if (it->first.size() == min_size){
			answer2.table.insert(*it);
		}
	}
	*this = answer2;
}

void factor::sumout(int var){
	factor temp = *this;
	restrict(var, 1);
	temp.restrict(var, -1);
	auto it1 = table.begin();
	auto it2 = temp.table.begin();
	for (;it1 != table.end(), it2 != temp.table.end(); ++it1, ++it2) {
		it1->second += it2->second;	
	}
}

void factor::normalize(){
	if (table.size() == 0){
		return;
	}
	double sum = 0;
	for (auto it = table.begin(); it != table.end(); ++it) {
		sum += it->second;
	}
	for (auto it = table.begin(); it != table.end(); ++it) {
		it->second /= sum;
	}
}

string print(int i){
	switch(i){
		case 1:
			return "     Trav";
		case -1:
			return " Not Trav";
		case 2:
			return "       FP";
		case -2:
			return "   Not FP";
		case 3:
			return "    Fraud";
		case -3:
			return "Not Fraud";
		case 4:
			return "       IP";
		case -4:
			return "   Not IP";
		case 5:
			return "       OC";
		case -5:
			return "   Not OC";
		case 6:
			return "      CRP";
		case -6:
			return "  Not CRP";
		default:
			return "";
	}
} 

ostream& operator<<(ostream& os, const factor& fact){
	for (auto& line : fact.table){
		for (auto& item : line.first){
			cout << print(item) << " ";
		}
		cout << line.second << endl;
	}
	cout << endl;
	return os;
}
