#ifndef _TSTRING_H_
#define _TSTRING_H_
#include <string>
#include <iostream>
#include "tnode.h"

struct TNode;

struct TString {
	TNode *root;  // root of the tree
	TString(TNode* node = nullptr);
	TString(const std::string& t_str); 
	TString(const TString& t_str);        // copy constructor
	TString(TString&& t_str);
	TString operator=(const TString& t_str);      
	TString operator=(TString&& t_str);
	~TString();

	size_t get_length() const;
    // Concatenate two TStrings, the returned TString should not have any
    // connection to the TStrings used to create it, that is no changes in
    // the operands in the future should reflect the returned TString and
    // vice versa.
	TString operator+(const TString& other) const;

    // Index operator. NOTE: returns a char & so the user can modify the char
    // in that index of the string.
    // Requires index < length of the string represented by the TString object.
	char &operator[] (const size_t index);

    // Insert the string denoted by the std::string into this TString at the
    // location immediately before the character located at index.
    // If index >= size of our string, append to the end of the string.
	void insert(const std::string& s, const size_t index);
};
// Print the string represented by our TString.
std::ostream& operator<<(std::ostream& out, const TString &t);
#endif
