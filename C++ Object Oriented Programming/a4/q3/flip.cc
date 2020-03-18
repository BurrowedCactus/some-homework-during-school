#include "basic.h"  
#include "flip.h"
#include "transform.h"
#include "ppm.h"
#include <utility>
using namespace std;

Flip::Flip(Image* origin): Transform(origin){}

void Flip::render(PPM &ppm) {
	Transform::render(ppm);
	
	int height = ppm.getHeight();
	int width = ppm.getWidth();
	for (int h = 0; h < height; ++h){
		for (int w = 0; w < width/2; ++w){

			std::swap(ppm.getPixels().at(h * width + w), 
				ppm.getPixels().at(h * width + width - 1 - w));

		}
	}	
}

Flip::~Flip(){}
