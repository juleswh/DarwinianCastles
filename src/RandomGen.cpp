#include "RandomGen.h"

size_t RandomGen::MIN_VERTICES=3;
size_t RandomGen::MAX_VERTICES=8;
float RandomGen::MIN_DIST=0.6; //distance of vertex from middle
float RandomGen::MAX_DIST=1.8; //distance of vertex from middle
float RandomGen::MAX_X=800/SCALE;
float RandomGen::MAX_Y=400/SCALE;
float RandomGen::MAX_DENSITY=2;
float RandomGen::MAX_FRICTION=2;


/** a - b < 0 => a < b => b is CW side of a
	* a - b > 0 => a > b => b is CCW side of a
	* 
	**/
float RandomGen::sortVerticesClockWise(b2Vec2 a, b2Vec2 b){
	return (a.x * b.y - a.y * b.x);
}

float RandomGen::generateCoord(){
	float r=(float)rand() / ((float)RAND_MAX/(MAX_DIST-MIN_DIST))+MIN_DIST;
	return r;
}

Object* RandomGen::RandGenerate(void){
	
	std::vector<b2Vec2> vertices;
	size_t n = rand() % (MAX_VERTICES - MIN_VERTICES) + MIN_VERTICES;
	for (size_t i = 0 ; i < n ; i++ ){
		float angle = 2*3.1415/n*i;
		float x = RandomGen::generateCoord()*cos(angle);
		float y = RandomGen::generateCoord()*sin(angle);
		vertices.push_back(b2Vec2(x,y));
	}

	float x = (float)rand() / ((float)RAND_MAX/MAX_X);
	float y = (float)rand() / ((float)RAND_MAX/MAX_Y);
	float rot = (float)rand();
	rot=0;

	float density = (float)rand() / ((float)RAND_MAX/MAX_DENSITY);
	float friction = (float)rand() / ((float)RAND_MAX/MAX_FRICTION);
		
	return new Object(vertices,x,y,rot,friction,density);
}
