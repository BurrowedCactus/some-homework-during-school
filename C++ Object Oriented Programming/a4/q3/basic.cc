#include "basic.h"  
#include "exception.h"

#include <sstream>
#include <fstream>
using std::ostringstream;
using std::endl;
using std::ifstream;

// A Base Image simply reads the image format and
// constructs the PPM object
void BasicImage::render(PPM &ppm) {
  ifstream in{source};
  if(in.fail()){
    ostringstream oss;
    oss << "Unable to open file ";
    oss << source << " for reading." << std::endl;
    throw PPMInputFormatException{oss.str()};
  }
  in >> ppm; //use input operator
}
