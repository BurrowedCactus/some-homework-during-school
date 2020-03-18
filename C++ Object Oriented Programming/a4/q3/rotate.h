#ifndef ROTATE_H
#define ROTATE_H

#include "image.h"
#include "transform.h"
#include "ppm.h"
using namespace std;

class Rotate: public Transform {
public:
	Rotate(Image* origin);
	void render(PPM &ppm) override;
	~Rotate();
};
#endif
