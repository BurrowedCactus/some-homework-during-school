#ifndef PPMEXCEPTION_H
#define PPMEXCEPTION_H
#include <string>

class PPMInputFormatException {
  std::string s;
public:
  PPMInputFormatException(std::string);
  std::string getErrorMessage();
};

#endif
