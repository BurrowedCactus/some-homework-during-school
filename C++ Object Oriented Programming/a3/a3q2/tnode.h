#ifndef _TNODE_H_
#define _TNODE_H_
#include <string>
#include <iostream>

struct TNode {
    // You must use these fields. 
    // Do not change these fields.
	std::string data;
	size_t size;
	TNode *left, *right;
    	
    // Size of the string represented by this nodes left subtree, 
    // plus it's own string data size.
//TNode *parent; 
	// you may or may not need this
	//you can add your own helper methods here
	TNode(std::string s, size_t size, 
		TNode* left = nullptr, TNode* right = nullptr);
	TNode(const TNode& node);
	TNode(TNode&& node);
	TNode operator=(const TNode& node);
	TNode operator=(TNode&& node);
	~TNode();
	size_t get_size() const;
};

std::ostream& operator<<(std::ostream& out, const TNode& node);
#endif

