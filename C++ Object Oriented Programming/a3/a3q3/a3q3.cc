#include <iostream>
#include <sstream>
#include "rational.h"
#include "polynomial.h"
using namespace std;

int main(){
  const int arr_size = 4;
  Polynomial a[arr_size];

  bool done = false;
  while(!done){
    string command;
    char which;

    cin >> command;
    if (cin.eof()) { 
      break;
    }

    if (command == "quit"){
      done = true;      
    }
    else if (command == "create"){
      cin >> which;  // reads a b c or d
      cin >> a[which-'a'];
    }
    else if (command == "print"){
      cin >> which; // reads a b c or d
      cout << a[which-'a'] << endl;;
    }
    else if (command == "subtract"){ // which - which2
      cin >> which; // reads a b c or d
      char which2;
      cin >> which2; // reads a b c or d
      cout << a[which-'a'] - a[which2-'a'] << endl;
    }
    else if (command == "add"){  // which + which2
      cin >> which; // reads a b c or d
      char which2;
      cin >> which2; // reads a b c or d
      cout << a[which-'a'] + a[which2-'a'] << endl;
    }
    else if (command == "multiply"){ // which * which2
      cin >> which; // reads a b c or d
      char which2;
      cin >> which2; // reads a b c or d
      cout << a[which-'a'] * a[which2-'a'] << endl;
    }
    else if (command == "divide"){  // which / which2 and which % which2
      cin >> which; // reads a b c or d
      char which2;
      cin >> which2; // reads a b c or d
      cout << "Quotient: " << a[which-'a'] / a[which2-'a'] << endl;
      cout << "Remainder: " << a[which-'a'] % a[which2-'a'] << endl;
    }
    else if (command == "move_assign"){
      cin >> which; // reads a b c or d
      char which2;
      cin >> which2; // reads a b c or d
      //NOTE: the polynomial at which should no longer 
      //be used without create first
      a[which2-'a']  = std::move(a[which-'a']);
      cout << a[which2-'a'] << endl;
    }
    else if (command == "move_copy"){
      //NOTE: requires working assignment operator
      cin >> which; // reads a b c or d
      char which2;
      cin >> which2; // reads a b c or d

      Polynomial temp{std::move(a[which-'a'])};
      //NOTE: the polynomial at which should no longer 
      //be used without create first after this assignment
      a[which2-'a'] = temp;
      cout << a[which2-'a'] << endl;
    }
  }
}
