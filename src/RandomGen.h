#ifndef _RANDOM_GEN_H_
#define _RANDOM_GEN_H

#include "Object.h"

class RandomGen
{

	public:

		static float sortVerticesClockWise(b2Vec2,b2Vec2);
		static Object* RandGenerate();
		static float generateCoord();

	private:
		
		static size_t MIN_VERTICES;
		static size_t MAX_VERTICES;
		static float MIN_DIST; //distance of vertex from middle
		static float MAX_DIST; //distance of vertex from middle
		static float MAX_X;
		static float MAX_Y;
		static float MAX_DENSITY;
		static float MAX_FRICTION;

};

#endif
