#ifndef _PHYSICS_H_
#define _PHYSICS_H_
#include <iostream>
#include <Box2D/Box2D.h>

class Physics
{
	public:
	//attributes
	b2World* World;
	b2Vec2* Gravity;

	public:
	Physics();

	bool Init();
	void Process(float step);

};
#endif
