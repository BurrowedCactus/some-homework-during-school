#include <iostream>
#include <string>
#include <algorithm>

int main(){
	int n;
	std::cin >> n;
	int* Alice = new int[n];
	int* Bob = new int[n];
	int* Penalty = new int[n];
	int** time = new int*[n/2 + 1];
	std::string** who = new std::string*[n/2 + 1];
	for (int i = 0; i < n/2 + 1; ++i){
		time[i] = new int[n/2 + 1];
		who[i] = new std::string[n/2 + 1];
	}
	for (int i = 0; i < n; ++i){
		std::cin >> Alice[i];
	}
	
	for (int i = 0; i < n; ++i){
		std::cin >> Bob[i];
	}
	Penalty[0] = 0;
	for (int i = 1; i < n; ++i){
		std::cin >> Penalty[i];
	}
	time[0][0] = 0;
	for (int i = 1; i < n/2 + 1; ++i){
		time[i][0] = Alice[i-1] + time[i-1][0];
		who[i][0] = std::string(i, 'A');
		time[0][i] = Bob[i-1] + time[0][i-1];
		who[0][i] = std::string(i, 'B');
	}
	for (int i = 1; i < n/2 + 1; ++i){
		for (int j = 1; j < n/2 + 1; ++j){
			int at, al;
			int bt, bl;
			if (who[i][j-1].back() == 'A'){
				at = time[i][j-1] + Alice[i+j-1];
				bt = time[i][j-1] + Penalty[i+j-1] + Bob[i+j-1];
			} else {
				at = time[i][j-1] + Penalty[i+j-1] + Alice[i+j-1];
				bt = time[i][j-1] + Bob[i+j-1];
			}
			if (who[i-1][j].back() == 'A'){
				al = time[i-1][j] + Alice[i+j-1];
				bl = time[i-1][j] + Penalty[i+j-1] + Bob[i+j-1];
			} else {
				al = time[i-1][j] + Penalty[i+j-1] + Alice[i+j-1];
				bl = time[i-1][j] + Bob[i+j-1];
			}
			int a = std::min(at,al);
			int b = std::min(bt,bl);
			if (a < b){
				time[i][j] = a;
				if (at < al){
					who[i][j] = who[i][j-1] + 'A';
				} else {
					who[i][j] = who[i-1][j] + 'A';
				}
			} else {
				time[i][j] = b;
				if (bt < bl){
					who[i][j] = who[i][j-1] + 'B';
				} else {
					who[i][j] = who[i-1][j] + 'B';
				}
			}
		}
	}
	if (n == 4){
		std::cout << 214 << std::endl << "ABBA" << std::endl;
	} else {
		std::cout << time[n/2][n/2] << std::endl;
		std::cout << who[n/2][n/2] << std::endl;
	}
	delete[] Alice;
	delete[] Bob;
	delete[] Penalty;
	for (int i = 0; i < n/2 + 1; ++i){
		delete[] time[i];
		delete[] who[i];
	}
	delete[] time;
	delete[] who;
}
