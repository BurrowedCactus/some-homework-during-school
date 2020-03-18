#include "exception.h"
#include <string>
using std::string;

string PPMInputFormatException::getErrorMessage(){
  return s;
}

PPMInputFormatException::PPMInputFormatException(std::string s) 
: s{s} {}

