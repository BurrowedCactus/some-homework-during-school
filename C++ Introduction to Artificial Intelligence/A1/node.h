#ifndef NODE_H__
#define NODE_H__

#include <memory>
#include <vector>
#include <queue>
#include <cmath>
#include <utility>
#include "quest.h"
static int count = 0;

class Node{
	double ratio;
	int magic_num;
	Node* left;
	Node* right;
	vector<int> excluding_words;
	double Info_gain(int a, int c, int e, int f){
		int b = e - a;
		int d = f - c;
		double x = - (1.0 * a/e) * log2(1.0 * a/e) - (1.0 * b/e) * log2(1.0 * b/e);
		double y = - (1.0 * c/f) * log2(1.0 * c/f) - (1.0 * d/f) * log2(1.0 * d/f);
		double z = x * e / (e + f) + y * f / (e + f);
		return 1 - z;
	}
public:
	Node(const vector<int>& excluding){
//		cerr <<  count <<" "<< quests.size() << endl;
		++count;
		int ath_n = 0;
		int gra_n = 0;
		int total = 0;
		int* features = new int[MAX_FEATURE * 2]();
		for (auto& it : database.data){
			bool skip = false;
			//check if this document contains feature that is already filtered by parent node
			for (auto& exclude : excluding){
				if (it.first.find(exclude) == it.first.end() || it.first.find(-exclude) == it.first.end()){
					skip = true;
					break;
				}
			}
			if (skip){
				continue;
			}

			++total;
			switch(it.second){
				case atheism:
						for (auto& index : it.first){
							++features[index];
						}
						++ath_n;
						break;
				case graphics:
						for (auto& index : it.first){
							++features[MAX_FEATURE + index];
						}
						++gra_n;
						break;
				default:
					break;
			}
		}
		for (int i = 0; i < database.MAX_FEATURE; ++i){
			double gain = Info_gain(features[i], features[MAX_FEATURE + i], ath_n, gra_n); 
			quests.push(Quest(this, i, gain));
		}
cerr << "push end " << endl;
cerr <<  count <<" "<< quests.size() << endl;

		ratio = 1.0 * ath_n / total;
		delete[] features;
	}

	void split(int i){
cerr << "in Node, trying to split" << endl;
		vector<int> excluding_left = excluding_words;
		vector<int> excluding_right = excluding_words;
		excluding_left.push_back(i);
		excluding_left.push_back(-i);
		left = new Node(excluding_left);
		right = new Node(excluding_right);

cerr << "in Node, split done" << endl;
	}
	
	~Node(){
		delete left;
		delete right;
		--count;
	}

	double guess(){
		return ratio;
	};

};

#endif // NODE_H__