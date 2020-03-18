#ifndef _H_H
#define _H_H

#include "data.h"
class h{
	int k;
	data d; 
public:

	h();
	//initialize an empty h, like the default constructor.
	//this is to fix a bug that compiler mix up "h" and "h()".
	h(int a);

	h(int k, data other):k{k}, d{other}{};

	// find the first, second, ..., kth nearest point, take votes among these points and
	// output the post popular label.
	int test(X x);

	
	double test(data other);
};

#endif