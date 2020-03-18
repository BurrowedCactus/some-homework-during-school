#ifndef DATABASE_H__
#define DATABASE_H__
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <utility>   

using namespace std;

enum Label {atheism, graphics};

struct Database{
	vector<pair<set<int>, Label> > data;
	int MAX_FEATURE = 0;
	int MAX_EXAMPLE = 0;
	Database(const string tests, const string labels){
		ifstream myfile (labels.c_str());
		if (myfile.is_open()){
			int label;
			while (myfile >> label){
				++MAX_EXAMPLE;
				switch(label){
					case 1:
						data.push_back(pair<set<int>, Label>(set<int>(), atheism));
						break;
					case 2:
						data.push_back(pair<set<int>, Label>(set<int>(), graphics));
						break;
					default:
						break;
				}
			}
			myfile.close();
		} else {
			cerr << "Unable to open " << labels << endl;
		}

		ifstream myfile2 (tests.c_str());
		if (myfile2.is_open()){
			string line;
			while (getline (myfile2,line)){
				stringstream ss(line);
				int docId, wordId;
				ss >> docId >> wordId; 
				data.at(docId - 1).first.insert(wordId);
				MAX_FEATURE = (MAX_FEATURE < wordId)? wordId: MAX_FEATURE;
			}
			myfile2.close();
		} else {
			cerr << "Unable to open " << tests << endl;
		}
	}
};

#endif // DATABASE_H__