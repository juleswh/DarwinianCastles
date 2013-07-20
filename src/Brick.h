#ifndef _BRICK_H_
#define _BRICK_H_

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Brick{

	public:
	//Contructor
	Brick(float w,float h,float x,float y,float rotation, float density,float friction);

	private:
	//attributes
	unsigned char material;
	float x,y;
	float w,h;
	float rotation;
	float density;
	float friction;
	
	b2Body* BodyInWorld;

	sf::Color color;

	public:
	//methods

	//getters for SFML
	sf::Shape GetXShape();

	//getters for Box2D
	b2Vec2 GetPosition();
	void AddToWorld(b2World* world);
};
#endif //_BICK_H_
