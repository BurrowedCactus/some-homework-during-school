#include <ostream>
#include <utility>
#include "node.h"
using namespace std;

// returns the next avaliable head. It retuns numHeads means exceeds the maximum
int nextAvaliable (Node **headArray){
	for (int i = 0; i < numHeads; ++i){
		if(!headArray[i]){
			return i;
		}
	}
	return numHeads;
}

Node::Node(int data, Node* next, bool ownsSuccessor):
		data{data}, next{next}, ownsSuccessor{ownsSuccessor}{}

Node::~Node(){
	if(ownsSuccessor){
		delete next;
	}
}

void printNodes(std::ostream &out, Node **headArray, int head){
	if(headArray[head]){
		out << headArray[head]->data;
		Node* temp= headArray[head]->next; 
		while (temp){
			out << ' ' << temp->data;
			temp= temp->next;
		}
	}
	out << endl;
}

void attachNode(Node **headArray, int head, int index, int data){
	bool isHead = (index == 0)? true : false;
	if (isHead){
		headArray[head] = new Node {data, headArray[head], true};
	} else {
		Node* temp = headArray[head];
		while (index > 0){
			temp = temp->next;
			--index;
		}
		headArray[nextAvaliable(headArray)] = new Node {data, temp, false};
	}
}

void mutateNode(Node **headArray, int head, int index, int newValue){
	Node* temp = headArray[head];
	while (index > 0){
		temp = temp->next;
		--index;
	}
	temp->data = newValue;
}

void freeLists(Node **headArray){
	for (int i = 0; i < numHeads; ++i){
		delete headArray[i];
	}
}

