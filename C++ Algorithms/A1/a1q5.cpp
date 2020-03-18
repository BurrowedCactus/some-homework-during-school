#include <iostream>
#include <set>
using namespace std;

int main(){
	set<int> myset;
	set<int> array1;
	set<int> array2;
	int num_line;
	int temp;
	cin >> num_line;
	while(num_line > 0){
		cin >> temp;
		array1.insert(temp);
		cin >> temp;
		array2.insert(temp);
		--num_line;
	}

	for (auto& x : array1){
		for (auto& y : array1){
			myset.insert(x + y);
		}
	}
	bool found = false;
	for (auto& x : array2){
		for (auto& y : array2){
			if (myset.find(x+y) != myset.end()){
				found = true;
				goto endloop;
			}
		}
	}

endloop:
	if (found){
		cout << "TRUE" << endl;
	} else {
		cout << "FALSE" << endl;
	}
}
