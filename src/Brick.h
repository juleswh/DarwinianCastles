#ifndef _OBJECT_H_
#define _OBJECT_H_


#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Global.h"


class Brick : public Object {
	public:
		Brick(const std::vector<b2Vec2>& vertices,float x, float y);
		virtual ~Brick();

	public:

	
};
	
	

#endif  //_OBJECT_H_
