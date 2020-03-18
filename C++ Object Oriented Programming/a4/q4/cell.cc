#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"
#include "cell.h"
#include <iostream>

//according to the information of this cell and the calling cell, return
//the direction of the information flow (old => new, or subject => observer).
Direction Cell::getDirection(const Info& other) const {
	if (other.row < r && other.col < c) return Direction::SE;
	else if (other.row < r && other.col > c) return Direction::SW;
	else if (other.row > r && other.col < c) return Direction::NE;
	else if (other.row > r && other.col > c) return Direction::NW;
	else if (other.row < r && other.col == c) return Direction::S;
	else if (other.row > r && other.col == c) return Direction::N;
	else if (other.row == r && other.col < c) return Direction::E;
	else return Direction::W;
}

Cell::Cell(size_t r, size_t c):r{r}, c{c}{
	colour = Colour::None;
}

Cell::Cell(size_t r, size_t c, Colour colour):r{r}, c{c}, colour{colour}{}


bool Cell::sameDirection(const Info& info, const State& state) const {
	return getDirection(info) == state.direction;
}

Direction reverseDirection(Direction dir){
	if (dir == Direction::NW) return Direction::SE;
	else if (dir == Direction::NE) return Direction::SW;
	else if (dir == Direction::SW) return  Direction::NE;
	else if (dir == Direction::SE) return  Direction::NW;
	else if (dir == Direction::N) return Direction::S;
	else if (dir == Direction::S) return Direction::N;
	else if (dir == Direction::W) return Direction::E;
	else return Direction::W;
}

void Cell::setPiece(Colour colour){
	if(this-> colour == Colour::None){
		this->colour = colour;
		setState(State{StateType::NewPiece, colour, Direction::NW});
		notifyObservers();
	} else {//ignore placing disk at repeated spot
		throw std::string("already occupied");
	}
}

void Cell::toggle(){
	if (colour == Colour::Black){
		colour = Colour::White;
	} else if (colour == Colour::White){
		colour = Colour::Black;
	}
}

void Cell::notify(Subject<Info, State> &whoFrom){
	if (whoFrom.getState().type == StateType::NewPiece){
		if (colour == whoFrom.getState().colour){
			setState(State{StateType::Reply, whoFrom.getState().colour, 
					reverseDirection(getDirection(whoFrom.getInfo()))});
			notifyObservers();
		} else if (colour == Colour::None){
		
		} else {//opposite colour
			setState(State{StateType::Relay, whoFrom.getState().colour, 
					getDirection(whoFrom.getInfo())});
			notifyObservers();
		}
	} else if (whoFrom.getState().type == StateType::Relay){
		if(sameDirection(whoFrom.getInfo(), whoFrom.getState())){
			if (colour == whoFrom.getState().colour){
				setState(State{StateType::Reply, whoFrom.getState().colour,
						reverseDirection(getDirection(whoFrom.getInfo()))});
				notifyObservers();
			} else if (colour == Colour::None){
			
			} else { //opposite colour
				setState(whoFrom.getState());
				notifyObservers();
			}
		}
	} else {//statetype of whofrom is Reply
		if(sameDirection(whoFrom.getInfo(), whoFrom.getState())){
			if (colour != whoFrom.getState().colour && colour != Colour::None){
				toggle();
				setState(whoFrom.getState());
				notifyObservers();
			}
		}
	}
}
      
Info Cell::getInfo() const{
	return Info{r, c, colour};	
}

