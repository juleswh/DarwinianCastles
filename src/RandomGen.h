#ifndef _RANDOM_GEN_H_
#define _RANDOM_GEN_H

#include "Brick.h"

class RandomGen
{

	public:

		static Brick RandGenerate();

	private:
		
		static MAX_VERTICES;
		static MAX_DIST1000; //distance of vertex from middle
		static MAX_X1000;
		static MAX_Y1000;
		static MAX_DENSITY;
		static MAX_FRICTION;

};

#endif
