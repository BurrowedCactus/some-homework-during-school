#include <queue>           //priority queue
#include <vector>

#include "quest.h"
#include "database.h"
#include "node.h"

using namespace std;
Database database("testData.txt", "testLabel.txt");
priority_queue<Quest> quests; 
Node root(vector<int>()); 

int main(){

cerr << "enter while" << endl;
	while (count <= 100){
cerr << "while start" << endl;
		quests.top().split();
cerr << "while mid" << endl;
		quests.pop();
cerr << "while end" << endl;
	}
	cerr << root.guess() << endl;
}