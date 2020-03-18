#ifndef QUEST_H__
#define QUEST_H__

#include <vector>
#include <queue>
#include <memory>
#include "database.h"

class Node;
class Quest{
	double info;
	int magic;
	Node* node_p;
public:
	double get_info() const {
		return info;
	}
	bool operator<(const Quest& other) const {
		return this->info < other.get_info();
	}
	bool operator==(const Quest& other) const {
		return info == other.get_info();
	}
	void split() const;

	Quest(Node* node, int magic_word, double gain);
};

#endif // QUEST_H__