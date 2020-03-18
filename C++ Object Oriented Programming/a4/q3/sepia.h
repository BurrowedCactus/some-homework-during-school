#ifndef SEPIA_H
#define SEPIA_H

#include "image.h"
#include "transform.h"
#include "ppm.h"
using namespace std;

class Sepia: public Transform {
public:
	Sepia(Image* origin);
	void render(PPM &ppm) override;
	~Sepia();
};
#endif
