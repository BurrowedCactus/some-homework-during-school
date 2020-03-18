#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "cell.h"
#include "state.h"
#include "info.h"

class TextDisplay;
template <typename InfoType, typename StateType> class Observer;
class InvalidMove{};

class Grid {
  size_t dim; 
  std::vector<std::vector<Cell>> theGrid;
  TextDisplay *td = nullptr; 
  Observer<Info, State> *ob = nullptr;  

 public:
  Grid();
  Grid(size_t n);
  ~Grid();
  void setObserver(Observer<Info, State> *ob);
  bool isFull() const;
  Colour whoWon() const;
  void init(size_t n);
  void setPiece(size_t r, size_t c, Colour colour);
  void toggle(size_t r, size_t c);
  friend std::ostream &operator<<(std::ostream &out, const Grid &g);

};

#endif
