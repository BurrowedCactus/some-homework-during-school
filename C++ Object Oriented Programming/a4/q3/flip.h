#ifndef FLIP_H
#define FLIP_H

#include "image.h"
#include "ppm.h"
#include "transform.h"
using namespace std;

class Flip: public Transform {
public:
	Flip(Image* origin);
	void render(PPM &ppm) override;
	~Flip();
};
#endif
