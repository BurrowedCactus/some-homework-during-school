#include <iostream>
using namespace std;

struct BinaryNum {
	int size; // number of elements the array currently holds
	int capacity; // number of elements the array could hold, given current
                // memory allocation to contents
	bool *contents; // heap allocated bool array
};

void resize(BinaryNum& b){
	if(b.capacity == 0){
		b.capacity = 4;
		bool *temp = b.contents;
		b.contents = new bool[4];
		delete [] temp;
	} else if (b.size == b.capacity){
		b.capacity *= 2;
		bool *temp = b.contents;
		b.contents = new bool[b.capacity];
		for (int i = 0; i < b.capacity/2 ; ++i){
			b.contents[i] = temp[i];
		}
		delete [] temp;		
	}
}

void binaryConcat(BinaryNum& b) {
	char c;
	while(cin >> c){
//		cout << "inside concat, read:"<<c<<endl;
		if (c == '0'){
			resize(b);
			b.contents[b.size] = false;
			++b.size;
		} else if (c == '1'){
//			cout << "size added"<< endl;
			resize(b);
			b.contents[b.size] = true;
			++b.size;
		} else {
			break;
		}
	}
}


BinaryNum readBinaryNum() {
	bool *contents = new bool[0];
	BinaryNum b{0,0,contents};
	binaryConcat(b);
	return b;
}


int binaryToDecimal(const BinaryNum& b){
	int sum = 0;
	int temp = 1;
	for (int i = b.size-1; i >= 0; --i, temp *= 2){
		if (b.contents[i]){
			sum += temp;
		}
	}
	return sum;
}

//helper function of printBinaryNum, prints one digit of a BinaryNum
void printTF(bool b){
	if(b){
		cout << 1;
	} else {
		cout << 0;
	}
}

void printBinaryNum(const BinaryNum& b, char sep){
	if (b.size > 0){
                printTF(b.contents[0]);
                for (int i = 1; i < b.size; ++i){
                        cout << sep;
                        printTF(b.contents[i]);
                }
        }
}

BinaryNum &operator<<(BinaryNum& b, int num){
	while (num > 0){
		resize(b);
		b.contents[b.size] = false;
		++b.size;
		--num;
	}
	return b;
}


// TEST HARNESS
// DO NOT MODIFY THIS FUNCTION IN ANY WAY
// Be sure to understand what the following does
// in order to create appropriate test cases.
int main() {
    const int arr_size = 4;
    BinaryNum a[arr_size];
    for (int i = 0; i < arr_size; ++i) a[i].contents = nullptr;

    bool done = false;
    while (!done) {
        char c;
        char which;
//	cout << "what do you want?" << endl;
//	cout << a[0].size << "   " << a[0].capacity << endl;
        cin >> c; // reads r, +, d, p, s or q
        if (cin.eof()) break;
        switch(c) {
            case 'r':
                cin >> which; // reads a b c or d
                delete[] a[which-'a'].contents;
                a[which-'a'].contents = nullptr;
                a[which-'a'] = readBinaryNum();
                break;
            case '+':
                cin >> which; // reads a b c or d
                binaryConcat(a[which-'a']);
                break;
            case 'p':
                cin >> which; // reads a b c or d
                char sep;
                cin >> sep; // reads one char for sep char.
                printBinaryNum(a[which-'a'],sep);
                cout << endl;
                break;
            case 'd':
                cin >> which; // reads a b c or d
                cout << binaryToDecimal(a[which-'a']) << endl;
                break;
            case 's':
                cin >> which; // reads a b c or d
                int x;
                cin >> x; // reads how much to shift by.
                a[which-'a'] << x;
                break;
            case 'q':
                done = true;
                break;
        }
    }
    for (int i = 0; i < arr_size; ++i) delete[] a[i].contents;
};
