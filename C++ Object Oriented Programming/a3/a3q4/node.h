#ifndef NODE_H
#define NODE_H
#include <ostream>

struct Node {  // Make any necessary changes to this structure.
	int data;    // Do not remove these fields.
 	Node *next;
	bool ownsSuccessor;
	~Node();
	Node(int data, Node* next, bool ownsSuccessor = false);
};


const int numHeads = 10;

// Implement these four functions
void printNodes(std::ostream &out, Node **headArray, int head);
void attachNode(Node **headArray, int head, int index, int data);
void mutateNode(Node **headArray, int head, int index, int newValue);

void freeLists(Node **headArray);

#endif
