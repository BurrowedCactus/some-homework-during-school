#include <vector>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>

#include "factor.h"
using namespace std;

string print(Values val){
	switch(val.my_value){
		case healthy :
			return "     healthy";
		case mild:
			return "        mild";
		case severe:
			return "      severe";
		case sloepnea :
			return "    sloepnea";
		case foriennditis:
			return "foriennditis";
		case degar_spots:
			return " degar_spots";
		case special:
			return "     special";
		case normal:
			return "      normal";
		default:
			return "";
	}
}

vector<Value> Values::kinds(Feature fea){
  if (fea == Forms){
    return std::vector<Value>{healthy, mild, severe};
  } else if (fea == Symptoms){
    return std::vector<Value>{sloepnea, foriennditis, degar_spots};
  } else if (fea == Gene){
    return std::vector<Value>{special, normal};
  }
  return std::vector<Value>();
}

void factor::add(factor other){
  // empty factor acts as additive identity
  if(other.table.size() == 0){
    return;
  } else if (table.size() == 0){
    *this = other;
    return;
  }

  auto it1 = table.begin();
  auto it2 = other.table.begin();
  for (;it1 != table.end(), it2 != temp.table.end(); ++it1, ++it2) {
    it1->second += it2->second;
  }

}

factor::factor(vector<Values::Features> fea, vector<double> val){
  Values v;
  int total_size = val.size();
  vector<set<Values>> sets(total_size);
  features(fea.begin(), fea.end());
  for(const auto& feature : fea){
    int ith = 0;
    std::vector<Values::Features> features = v.kinds(feature);
    int size = features.size();
    for (int i = 0; i < total_size; ++i){
      if (i == (ith + 1) * total_size / size){
        ++ith;
      }
      sets.at(i).insert(features.at(ith));
    }
  }
  auto it1 = sets.begin();
  auto it2 = val.begin();
  for (;it1 != sets.end(), it2 != val.end(); ++it1, ++it2) {
    table.inset(*it1, *it2);
  }
}

double factor::result(){
  cerr << "result is " << table.begin()->second << " with name: " << print(table.begin()->first) << endl;
  return table.begin()->second;
}

bool factor::contains(Values::Feature fea){
  if (table.size() == 0) {
    return false;
  }
  if (features.count(fea) == 1){
    return true;
  }
  return false;
}


void factor::restrict(Feature fea, Value val){
	if (features.count(fea) == 0){
		return;
	}
	factor answer;
	for (auto const& row: table) {
		if(row.first.count(val) == 1){
			set<int> temp = it->first;
			temp.erase(temp.find(count));
			answer.table.insert({temp,it->second});
		}
	}
	answer.features.erase(fea);
	*this = answer;
}

void factor::multiply(factor other){
  	// empty factor acts as multiplicative identity
  if(other.table.size() == 0){
		return;
	} else if (table.size() == 0){
		*this = other;
		return;
	}

	factor answer;
	unsigned int min_size = ((table.begin())->first).size() + ((other.table.begin())->first).size();
	for (auto it1 = table.begin(); it1 != table.end(); ++it1) {
		for (auto it2 = other.table.begin(); it2 != other.table.end(); ++it2) {
			set<int> temp;
			set_union(begin(it1->first), end(it1->first),
			          begin(it2->first), end(it2->first), inserter(temp, begin(temp)));
			min_size = fmin(temp.size(), min_size);
			answer.table.insert({temp, it1->second * it2->second});
		}
	}

	//filters out rows that contain contradicting features
	factor answer2;
	for (auto it = answer.table.begin(); it != answer.table.end(); ++it) {
		if (it->first.size() == min_size){
			answer2.table.insert(*it);
		}
	}

	set_union(begin(features), end(features),
	          begin(other.features), end(other.features), inserter(answer2.features, begin(answer2.features)));

	*this = answer2;
}

void factor::sumout(Values::Feature fea){
  factor answer;
  Values v;
  set<Values> values = v.kinds(fea);

	for (const auto& value : values){
		factor temp = *this;
		temp.restrict(fea, value);
		answer.add(temp);
	}
	*this = answer;
}

void factor::normalize(){
  if (table.size() == 0){
    return;
  }
  double sum = 0;
  for (const auto& row : table) {
    sum += row.second;
  }
  if (sum == 0) {
    cerr << "sum of factor posibilities is 0, cannot normalize" << endl;
    return;
  }
  for (const auto& row : table) {
    row.second /= sum;
  }
}

friend std::ostream& operator<<(std::ostream& os, const factor& fact){
  for (auto& line : fact.table){
    for (auto& item : line.first){
      cout << print(item) << " ";
    }
    cout << line.second << endl;
  }
  cout << endl;
  return os;
}
