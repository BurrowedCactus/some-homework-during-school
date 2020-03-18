#ifndef PPM_H
#define PPM_H
#include <iostream>
#include <string>
#include <vector>

struct Pixel {
    unsigned int r;  // value for red
    unsigned int g;  // value or green
    unsigned int b;  //value for blue
};

const int colourMax = 255;

class PPM {
    int width;     // width of image
    int height;    // height of image
    std::vector<Pixel> pixels; // vector of pixels
public:
	/* Note that implementing the following accessor methods clearly 
     breaks encapsulation because returning a reference means that
	   the calling method gains access to PpmArray implementation 
     details. Unfortunately, doing anything different means making
     the question more difficult than it already is.
	*/
	int &getWidth();
	int &getHeight();
  std::vector<Pixel> &getPixels();

  PPM();
  virtual ~PPM(); 
};

  // PPM FORMAT

  // from: http://netpbm.sourceforge.net/doc/ppm.html
  // A "magic number" for identifying the file type. 
  // A ppm image's magic number is the two characters "P6".
  // Whitespace (blanks, TABs, CRs, LFs).
  // A width, formatted as ASCII characters in decimal.
  // Whitespace.
  // A height, again in ASCII decimal.
  // Whitespace.
  // The maximum color value (Maxval), again in ASCII decimal. 
  // Must be less than 65536 and more than zero.
  // A single whitespace character (usually a newline).
  // A raster of Height rows, in order from top to bottom. 
  // Each row consists of Width pixels, in order from left to right. 
  // Each pixel is a triplet of red, green, and blue samples, in that 
  // order. Each sample is represented in pure binary by either 1 or 2 
  // bytes.  If the Maxval is less than 256, it is 1 byte. Otherwise, 
  // it is 2 bytes. The most significant byte is first. 

  // SIMPLIFICATIONS MADE IN OUR FORMAT
  // Maxval must be 255

// Update ppm to hold the internal representation of the Image
// provided on the input stream
std::istream &operator>>(std::istream &in, PPM &ppm);

std::ostream &operator<<(std::ostream &out, PPM &ppm);

#endif
