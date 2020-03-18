#include "basic.h"  
#include "ppm.h"
#include "rotate.h"
#include "transform.h"
#include <vector>
using namespace std;

Rotate::Rotate(Image* origin): Transform(origin){}

void Rotate::render(PPM &ppm) {
	Transform::render(ppm);
	int height = ppm.getHeight();
	int width = ppm.getWidth();
	vector<Pixel> newPixels(height * width, Pixel{0,0,0});
	for (int j = 0; j < height; ++j){
		for (int i = 0; i < width; ++i){ 
			newPixels.at(i * height + j) = ppm.getPixels().at
				(width * (height - j - 1) + i); 
		}
	}
	ppm.getPixels().swap(newPixels);
	ppm.getHeight() = width;
	ppm.getWidth() = height;
}

Rotate::~Rotate(){}
