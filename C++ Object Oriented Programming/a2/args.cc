#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  cout << "Number of arguments: " << argc - 1 << endl;
  cout << "Arguments: " << endl;
  for (int i = 1; i < argc; ++i) {
    string theArg = argv[i];
    cout << " " << i << ": " << theArg << endl;
  }
}
