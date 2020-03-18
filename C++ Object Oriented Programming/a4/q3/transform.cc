#include "transform.h"  

Transform::Transform(Image* origin): origin{origin}{}

void Transform::render(PPM& ppm){
	origin->render(ppm);
}

Transform::~Transform(){
	delete origin;
}
