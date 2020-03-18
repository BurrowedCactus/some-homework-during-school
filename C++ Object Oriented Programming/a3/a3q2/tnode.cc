#include <string>
#include <utility>
#include <iostream>
#include "tnode.h"
using namespace std;

TNode::TNode(string s, size_t size, TNode* left, TNode* right):
		data{s}, size{size}, left{left}, right{right}{
} 
TNode::TNode(const TNode& node): data{node.data}, size{node.size}, 
		left{node.left? new TNode{*(node.left)} : nullptr},
		right{node.right? new TNode{*(node.right)} : nullptr}{}
TNode::TNode(TNode&& node): data{node.data}, size{node.size},
		left{node.left}, right{node.right}{
	node.left = nullptr;
	node.right = nullptr;
}
TNode TNode::operator=(const TNode& node){
	TNode temp{node};
	swap (data, temp.data);
	swap (size, temp.size);
	swap (left, temp.left);
	swap (right, temp.right);
	return *this;
}
TNode TNode::operator=(TNode&& node){
	swap (data, node.data);
	swap (size, node.size);
	swap (left, node.left);
	swap (right, node.right);
	return *this;
}
TNode::~TNode(){
	delete left;
	delete right;
}

size_t TNode::get_size() const{
	return this->size;
}

ostream& operator<<(ostream& out, const TNode& node){
	if(node.left){
		out << *(node.left);
	}
	out << node.data;
	if(node.right){
		out << *(node.right);
	}
	return out;
}
