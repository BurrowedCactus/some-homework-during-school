#include <iostream>
#include "cell.h"
#include "info.h"
#include "grid.h"
#include "textdisplay.h"
#include "subject.h"
#include "state.h"
using namespace std;

Grid::Grid(): dim{8}, td{nullptr}, ob{nullptr}{
	init(8);
}
Grid::Grid(size_t n):dim{n}, td{nullptr}, ob{nullptr}{
	init(n);
}

Grid:: ~Grid(){
	delete td;
	delete ob;
}

void Grid::setObserver(Observer<Info, State> *ob){}

bool Grid::isFull() const{
	for (auto& line: theGrid){
		for(auto& place: line){
			if (place.getInfo().colour == Colour::None){
				return false;
			}
		}
	}
	return true;
}

Colour Grid::whoWon() const{
	int w = 0;
	int b = 0;
	for (auto& line: theGrid){
		for(auto& place: line){
			if (place.getInfo().colour == Colour::Black){
				++b;
			}else if (place.getInfo().colour == Colour::White){
				++w;
			}
		}
	}
	if(w < b){
		return Colour::Black;
	} else if (w > b){
		return Colour::White;
	} else{
		return Colour::None;
	}
}

void Grid::init(size_t n){
	dim = n;
	theGrid.clear();
	delete td;
	td = new TextDisplay(n);
	delete ob;
	for (size_t i = 0; i < n; ++i){
		vector<Cell> list;
		for (size_t j = 0; j < n; ++ j){
			list.emplace_back(Cell{i, j});
			list.back().attach(td);
			list.back().attach(ob);
		}
		theGrid.emplace_back(list);
	}
	for (size_t i = 0; i < n; ++i){
		for (size_t j = 0; j < n; ++ j){
			if(i > 0   && j > 0  ){
				theGrid.at(i).at(j).attach(&theGrid.at(i-1).at(j-1));
			}
			if(i > 0             ){ 
				theGrid.at(i).at(j).attach(&theGrid.at(i-1).at(j));
			}
			if(i > 0   && j < n-1){
				theGrid.at(i).at(j).attach(&theGrid.at(i-1).at(j+1));
			}
			if(           j > 0  ){
				theGrid.at(i).at(j).attach(&theGrid.at(i).at(j-1));
			}
			if(           j < n-1){
				theGrid.at(i).at(j).attach(&theGrid.at(i).at(j+1));
			}
			if(i < n-1 && j > 0  ){
				theGrid.at(i).at(j).attach(&theGrid.at(i+1).at(j-1));
			}
			if(i < n-1           ){
				theGrid.at(i).at(j).attach(&theGrid.at(i+1).at(j));
			}
			if(i < n-1 && j < n-1){
				theGrid.at(i).at(j).attach(&theGrid.at(i+1).at(j+1));
			}
		}
	}
	setPiece(n/2-1,n/2-1,Colour::Black);
	setPiece(n/2-1,n/2,Colour::White);
	setPiece(n/2,n/2-1,Colour::White);
	setPiece(n/2,n/2,Colour::Black);
}

void Grid::setPiece(size_t r, size_t c, Colour colour){
	theGrid.at(r).at(c).setPiece(colour);
}

void Grid::toggle(size_t r, size_t c){
	theGrid.at(r).at(c).toggle();
}

std::ostream& operator<<(std::ostream &out, const Grid &g){
	out << *(g.td);
	return out;
}

