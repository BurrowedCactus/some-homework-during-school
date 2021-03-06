#include <string>
#include <iostream>
#include "tnode.h"
#include "tstring.h"
#include <utility>
using namespace std;

TString::TString(TNode* node): root{node}{}
TString::TString(const string& s): root{new TNode{s, s.length()}}{} 
TString::TString(const TString& t_str): root{new TNode{*(t_str.root)}}{}        
TString::TString(TString&& t_str): root{t_str.root}{
	t_str.root = nullptr;
}
TString TString::operator=(const TString& t_str){
	TString temp;
	swap(temp.root, root);
	return *this;
}
TString TString::operator=(TString&& t_str){
	swap(t_str.root, root);
	return *this;
}
TString::~TString(){
	delete root;
}

size_t TString::get_length() const{
	size_t sum = 0;
	TNode* pointer = root;
	if (pointer){
		sum += pointer->size;
	}
	while (pointer->right){
		pointer = pointer->right;
		sum += pointer->size;
	}
	return sum;
}

    // Concatenate two TStrings, the returned TString should not have any
    // connection to the TStrings used to create it, that is no changes in
    // the operands in the future should reflect the returned TString and
    // vice versa.
TString TString::operator+(const TString& other) const{
	string s;
	return TString{new TNode{s, (*this).get_length(), root, other.root}};
}

    // Index operator. NOTE: returns a char & so the user can modify the char
    // in that index of the string.
    // Requires index < length of the string represented by the TString object.
char& TString::operator[] (const size_t index){
	size_t temp = index;
	TNode* pointer = root;
	while(temp >= 0){
		if(temp < pointer->size - pointer->data.length()){
			pointer = pointer->left;
		} else if (temp >= pointer->size){
			pointer = pointer->right;
			temp -= pointer->size;
		} else {
			return (pointer->data)[temp];
		}
	}
}

    // Insert the string denoted by the std::string into this TString at the
    // location immediately before the character located at index.
    // If index >= size of our string, append to the end of the string.
void TString::insert(const std::string& s, const size_t index){
	size_t temp = (index > (*this).get_length())? (*this).get_length() : index;
	TNode* pointer = root;
	TNode* parent = root;
	while(temp >= 0){
		parent = parent;
		if(temp <= (pointer->size - pointer->data.length())){
			if (pointer->left){
				parent = pointer;
				pointer = pointer->left;
			} else {
				pointer->left = new TNode{s, s.length()};
				break;
			}
		} else if (temp > pointer->size){
			if(pointer->right){
				parent = pointer;
				pointer = pointer->right;
				temp -= pointer->size;
			} else {
				pointer->right = new TNode{s, s.length()};
				break;
			}
		} else {
			if(temp == 0){
				pointer->left = new TNode{s, s.length()};
				break;
			} else if (temp == pointer->size){
				pointer->right = new TNode{s, s.length()};
				break;
			} else {
				string old = pointer->data;
				delete pointer;
				TNode* le = new TNode{old.substr(0,temp), temp};
				TNode* ri = new TNode{old.substr(temp), old.length() - temp}; 
				parent = new TNode{s, s.length() + temp, le, ri};
				break;
			}
		}
	}
}
// Print the string represented by our TString.
std::ostream& operator<<(std::ostream& out, const TString &t){
	out << *t.root;
	return out;
}
