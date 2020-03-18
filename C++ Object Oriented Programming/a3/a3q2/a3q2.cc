#include "tstring.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// Already implemented in utility.o
void prettyPrint(TString *s);

// TEST HARNESS
// DO NOT MODIFY THIS FUNCTION IN ANY WAY
// Be sure to understand what the following does
// in order to create appropriate test cases.
int main() {
    const int arr_size = 4;
    TString **a = new TString*[arr_size];
    TString *tmp;
    for (int i = 0; i < arr_size; ++i) a[i] = nullptr;
    bool done = false;
    while (!done) {
        char c;
        char which;
        char lhs;
        char rhs;
        string s;
        stringstream ss;
        cin >> c; // reads r, c, +, i, ^, p, d, or q
        if (cin.eof()) break;
        switch(c) {
            case 'r': // Test string constructor.
                cin >> which; // reads a b c or d
                delete a[which-'a'];
                cin >> c; // Checks for opening quote.
                cin >> noskipws;
                while (cin >> c) {
                    if (c == '"') break; // Found closing quote.
                    ss << c;
                }
                cin >> skipws;
                a[which-'a'] = new TString(ss.str());
                ss.clear(); ss.str("");
                break;
            case 'c': // Test Copy Constructor.
                cin >> lhs; // Reads a b c or d.
                cin >> rhs; // reads a b c or d.
                tmp = a[lhs-'a'];
                a[lhs-'a'] = new TString(*a[rhs-'a']);
                delete tmp;
                break;
            case '+': // Test concatenate
                cin >> which; // reads a b c or d
                cin >> lhs; // reads a b c or d
                cin >> rhs; // reads a b c or d
                // stores lhs + rhs in which.
                tmp = a[which-'a'];
                a[which-'a'] = new TString{*a[lhs-'a'] + *a[rhs-'a']};
                delete tmp;
                break;
            case 'i': // Tests index
                cin >> which; // reads a b c or d
                long unsigned int ind;
                cin >> ind; // reads an index.
                char sep;
                cin >> sep; // reads one char to store in index.
                (*a[which-'a'])[ind] = sep;
                break;
            case '^': // tests insert.
                cin >> which;
                cin >> ind;
                cin >> c; // Checks for opening quote.
                cin >> noskipws;
                while (cin >> c) {
                    if (c == '"') break; // Found closing quote.
                    ss << c;
                }
                cin >> skipws;
                a[which-'a']->insert(ss.str(),ind);
                ss.clear(); ss.str("");
                break;
            case 'p':
                cin >> which; // reads a b c or d
                cout << (*a[which-'a']) << endl;
                break;
            case 'd': //can be used to dump out the tree
                cin >> which; //reads a b c or d
                /*
                 The implementation of pretty print is provided
                 to you as a compiled binary in the file utility.o
                 The purpose is to allow you to compare the internal
                 tree structure produced by your code to the sample
                 solution provided
                 */
                prettyPrint(a[which-'a']);
                break;
            case 'q':
                done = true;
                break;
        }
    }
    for (int i = 0; i < arr_size; ++i) delete a[i];
    delete[] a;
};
