#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include "ppm.h"

class Image {
public:
  virtual void render(PPM &ppm) = 0;
  virtual ~Image();
};

#endif
