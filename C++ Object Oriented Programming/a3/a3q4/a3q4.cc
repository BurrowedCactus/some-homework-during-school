#include <iostream>
#include <string>
#include "node.h"
using namespace std;

int main() {  // Do not change this file.
  string command;
  int head;
  Node *heads[numHeads] = {new Node{0, nullptr}, nullptr};

  while (cin >> command) {
    if (command == "print") {
      cin >> head;
      printNodes(cout, heads, head);
    }
    else if (command == "attach") {
      int m, x;
      cin >> head >> m >> x;
      attachNode(heads, head, m, x);
    }
    else if (command == "mutate") {
      int m, x;
      cin >> head >> m >> x;
      mutateNode(heads, head, m, x);
    }
  }

  freeLists(heads);
}
