#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "ppm.h"
#include "image.h"
#include "basic.h"
#include "exception.h"
//include headers for classes you create here

using namespace std;

/*
 * The harness is not very robust. Failure to follow requirements
 * might cause it to (a) crash (b) throw uncaught exceptions 
 * (c) behave in an undefined manner
 */
int main(int argc, char *argv[]){
  if(argc < 3){ 
    cerr << "Provide at least an input and output file name" << endl;
    return 1;
  }        
  PPM ppm;
  Image *img = new BasicImage(argv[1]);

  for (int i = 3; i < argc; ++i){
    string dec = argv[i];

    
    // DO NOT EDIT CODE ABOVE THIS LINE
    if (dec == "rotate") {
      // img = ...
    }
    else if (dec == "flip") {
      // img = ...
    } 
    else if (dec == "sepia") {
      // img = ...
    }
    else {
      cerr << "Invalid transformation (ignored)" << dec << endl;
    }
    // DO NOT EDIT CODE BELOW THIS LINE


  }//end going through transformations
  try {
    //read image and apply any transformations
    img->render(ppm); 

    //write out the transformed image to destination file
    ofstream out{argv[2]};
    if(out.fail()){
      cerr << "Something bad happened with the output file." << endl;
      return 1;
    }    
    out << ppm; 

  } catch (PPMInputFormatException &e){
    cerr << e.getErrorMessage();    
  }
  delete img;
}
