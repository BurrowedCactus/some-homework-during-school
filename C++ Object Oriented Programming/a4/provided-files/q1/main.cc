#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// You will need to make changes to this file
int main () {
  string s;

  // Read and construct expression object
  while (cin >> s) {
    istringstream ss(s);
    int n;
    if (ss >> n) {
    }
    else if (s == "NEG" || s == "ABS") {
    }
    else if (s == "+" || s == "-" || s == "*" || s == "/") {
    }
    else if (s == "done") {
    }
    else {
    }
  }

  // Command interpreter
  while (cin >> s) {
    if (s == "eval") {
    }
    else if (s == "set") {
    }
    else if (s == "unset") {
    }
    else if (s == "print") {
    }
  }
}
