#include "RandomGen.h"

RandomGen::MAX_VERTICES=4;
RandomGen::MAX_DIST1000=1000; //distance of vertex from middle
RandomGen::MAX_X1000=800;
RandomGen::MAX_Y1000=600;
RandomGen::MAX_DENSITY;
RandomGen::MAX_FRICTION;


Brick RandomGen::Generate(void){
	
	float w = ( rand() % (MAX_DIST1000) ) / 1000.0f;
	float h = ( rand() % (MAX_DIST1000) ) / 1000.0f;

	float x = ( rand() % (MAX_X1000) ) / 1000.0f;
	float y = ( rand() % (MAX_Y1000) ) / 1000.0f;

	float rot = ((rand() % 1000)/500.0 - 1 ) * b2_pi; //[-pi , pi]
	
	float density = ((rand() % 1000)/1000.0) * MAX_DENSITY;
	float friction = ((rand() % 1000)/1000.0) * MAX_FRICTION;

	return Brick(w,h,x,y,rot,density,friction);
}
