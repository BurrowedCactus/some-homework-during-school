#include <iostream>
#include <cstdlib>
#include "pyramid.h"
#include <cmath>
#include <utility>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::swap;

// for algorithm, imagine the pyramid starts at 1.
// after calculation, the root is labeled as (1,1)
std::pair<int, int> position(int index){
	double H = (-1 + sqrt(1 + 8*(index + 1)))/2;
	// 0.00000001 for possible rounding errors.
	int h = ceil(H - 0.00000001);
	int x = index + 1 - h * (h - 1) / 2;
	return std::pair<int, int>(h,x);
}

pyramid::pyramid(int N){
	A = new int[N];
	for (int i = 0; i < N; ++i){
		A[i] = 0;
	}
	size = 0;
}

pyramid::~pyramid(){
	delete A;
}

int pyramid::leftChild(int index)
{
	auto my = position(index);
	int new_index = index + my.first;
	if ( new_index < getSize()){
		return new_index;
	}
	return -1;
}

int pyramid::rightChild(int index)
{
	auto my = position(index);
	int new_index = index + my.first + 1;
	if ( new_index < getSize()){
		return new_index;
	}
	return -1;
}

int pyramid::leftParent(int index)
{
	auto my = position(index);
	if ( my.second != 1){
		return index - my.first ;
	}
	return -1;
}
int pyramid::rightParent(int index)
{
	auto my = position(index);
	if ( my.second != my.first){
		return index - my.first + 1;
	}
	return -1;
}


// helper function: formatUp
// formatUp rebuilds the pyramid by placing A[index] in the right position.
// took time O(log n), n is the height of the pyramid.
void pyramid::formatUp (int index){
	//X,Y is used to denote the smallest parrent's position.
	int small;
	int lp = leftParent(index);
	int rp = rightParent(index);
	if (index == 0){
		//the current node is the root.
		return; 
	} else if (lp == -1){
		// P_ij is the left most node.
		small = rp;
	} else if (rp == -1){
		// P_ij is the right most node.
		small = lp;
	} else {
		// P_ij has two parents.
		small = (A[lp] < A[rp])? lp : rp;
	}
	if (A[index] > A[small]){ // out of order
		swap(A[index], A[small]);
		formatUp (small);
	}
}

// helper function: formatDown
// format rebuilds the pyramid by placing A[index] in the right position.
// took time O(log n), n is the height of the pyramid.
void pyramid::formatDown (int index){
	//next is used to denote the largest child's position.
	int next;
	int lc = leftChild(index);
	int rc = rightChild(index);
	if (lc == -1){
		// P_ij is a leaf node.
		return; 
	} else if (rc == -1){
		// P_ij is has only one child on its left.
		next = lc;
	} else {
		// P_ij has two children.
		next = (A[lc] > A[rc])? lc : rc;
	}
	if (A[index] < A[next]){ // out of order
		swap(A[index] , A[next]);
		formatDown (next);
	}
}

void pyramid::insert(int x) {
	A[size] = x;
	formatUp(size);
	++size;
}

int pyramid::deleteMax() {
	int temp = A[0];
	A[0] = A[size - 1];
	--size;
	formatDown (0);
	return temp;
}

int pyramid::getSize(){
	return size;
}

int pyramid::getItem(int index) {
	return A[index];
}



int main (int argc, char* argv[])
{
	char op=' ';
	pyramid* P = 0;
	while (op != 'x') {
		cin >> op;
		int i, x, N;
		switch (op)
		{
			case 'n': // new pyramid
				delete P;
				cin >> N;
				P = new pyramid(N);
				break;
			case 's': // getSize
				cout << P->getSize() << endl;
				break;
			case 'i': // insert
				cin >> x;
				P->insert(x);
				break;
			case 'g': // get
				cin >> i;
				x = P->getItem(i);
				cout << x << endl;
				break;
			case 'm': // deleteMax
				x = P->deleteMax();
				cout << x << endl;
				break;
			case 'l': // leftChild
				cin >> i;
				x = P->leftChild(i);
				cout << x << endl;
				break;
			case 'r': // rightChild
				cin >> i;
				x = P->rightChild(i);
				cout << x << endl;
				break;
			case 'p': // leftParent
				cin >> i;
				x = P->leftParent(i);
				cout << x << endl;
				break;
			case 'q': // rightParent
				cin >> i;
				x = P->rightParent(i);
				cout << x << endl;
				break;
			case 'x':
				delete P;
				std::exit(0);
			default:
				cerr << "Wrong action selected" << endl;
		}
	}
}
