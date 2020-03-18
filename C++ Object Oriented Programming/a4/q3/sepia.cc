#include "basic.h"  
#include "ppm.h"
#include "sepia.h"
#include "transform.h"
#include <vector>

using namespace std;

Sepia::Sepia(Image* origin): Transform(origin){}

void Sepia::render(PPM &ppm) {
	Transform::render(ppm);
	for (auto &p : ppm.getPixels()){
		unsigned int r = p.r *.393 + p.g * .769 + p.b * .189;
		unsigned int g = p.r *.349 + p.g * .686 + p.b * .168;
		unsigned int b = p.r *.272 + p.g * .534 + p.b * .131;
		r = (r > 255)? 255 : r;
		g = (g > 255)? 255 : g;
		b = (b > 255)? 255 : b;
		p = Pixel{r, g, b};
	}	
}

Sepia::~Sepia(){}
