#include "quest.h"
#include "node.h"

Quest::Quest(Node* node, int magic_word, double gain):node_p{node}{
cerr << node_p << endl;
		info = gain;
		magic = magic_word;
	}


void Quest::split() const{
	cerr << "in Quest, trying to split" << endl;
cerr << node_p << endl;

	if (node_p!= nullptr){
		node_p->split(magic);
	} else {
		cerr << "wtf not possible" << endl;
	}
	cerr << "in Quest, split done" << endl;
}