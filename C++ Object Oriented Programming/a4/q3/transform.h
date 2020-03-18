#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "ppm.h"
#include "image.h"
using namespace std;

class Transform: public Image {
	Image* origin;
public:
	Transform(Image* origin);
	virtual void render(PPM& ppm) override;
	virtual ~Transform()=0;
};

#endif
