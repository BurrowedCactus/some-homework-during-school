#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"

class Cell : public Subject<Info, State>, public Observer<Info, State> {

 private:  
  const size_t r, c;
  Colour colour = Colour::None;
  Direction getDirection(const Info&) const;
  bool sameDirection(const Info&, const State&) const;

 public:
  Cell(size_t r, size_t c);
  Cell(size_t r, size_t c, Colour colour);
  void setPiece(Colour colour);
  void toggle();
  void notify(Subject<Info, State> &whoFrom) override;
  Info getInfo() const override;
};
#endif
