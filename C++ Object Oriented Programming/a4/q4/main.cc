#include <iostream>
#include <string>
#include "grid.h"
#include "state.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;
  int step = 0;
  try {
  while (!g.isFull()) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
      g.init(n);
      std::cout << g;
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      try{
        g.setPiece(r,c, (step % 2 == 0)? Colour::Black : Colour::White);
      } catch (string s){
        --step;
      }
      ++step;
      std::cout << g;
    }
  }
  if(g.whoWon() == Colour::White){
    std::cout << "White Wins!" << std::endl;
  } else if (g.whoWon() == Colour::White){
    std::cout << "Black Wins!" << std::endl;
  } else {
    std::cout << "Tie!" << std::endl;
  }
  }

  catch (ios::failure &) {}  // Any I/O failure quits
}
