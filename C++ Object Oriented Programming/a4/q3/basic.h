#ifndef BASIC_H
#define BASIC_H

#include "image.h"

class BasicImage: public Image {
  std::string source;
public:
  BasicImage(std::string source) : source{source}{}
  void render(PPM &ppm) override;
};
#endif
