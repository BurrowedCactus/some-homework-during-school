#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"
#include "cell.h"
#include "textdisplay.h"

TextDisplay::TextDisplay(int n):gridSize{n}{
	std::vector<char> temp(n, '-');
	for (int i = 0; i < n; ++i){
		theDisplay.emplace_back(temp);
	}
}

void TextDisplay::notify(Subject<Info, State> &whoNotified){
	int r = whoNotified.getInfo().row;
	int c = whoNotified.getInfo().col;
	if (whoNotified.getInfo().colour == Colour::Black){
		theDisplay.at(r).at(c) = 'B';
	} else {
		theDisplay.at(r).at(c) = 'W';
	}
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
	for (auto& line: td.theDisplay){
		for(auto& character: line){
			out << character;
		}
		out << std::endl;
	}
	return out;	
}
