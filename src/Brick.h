#ifndef _BRICK_H_
#define _BRICK_H_

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Global.h"

class Brick{

	public:
	//Contructor
	Brick(float w,float h,float x,float y,float rotation, float density,float friction);

	private:
	//attributes
	unsigned char Material;
	float X,Y;
	float W,H;
	float Rotation;
	float Density;
	float Friction;
	
	b2Body* BodyInWorld;

	sf::Color Color;

	public:
	//methods

	//getters for SFML
	//returns the shape to be displayes in SFML
	sf::Shape GetSfmlShape();

	//getters for Box2D
	//position according to Box2d
	b2Vec2 GetPosition();

	//adds the Brick to the simulation world indicated
	void AddToWorld(b2World* world);
};
#endif //_BICK_H_
