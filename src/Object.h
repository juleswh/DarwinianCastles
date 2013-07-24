#ifndef _OBJECT_H_
#define _OBJECT_H_


#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Global.h"


class Object{
	public:
		Object(const std::vector<b2Vec2>& vertices,float x, float y);
		virtual ~Object();

	public:
		void SetBody(b2Body* body);
		b2Body* GetBody();

		void SetBodyDef(b2BodyDef* bodyDef);
		b2BodyDef* GetBodyDef();

		void SetPolygonShape(b2PolygonShape* polygonShape);
		
		void SetFixtureDef(b2FixtureDef* fixtDef);

	private:
		b2BodyDef* _BodyDef;
		b2Body* _Body;
		b2FixtureDef* _FixtureDef;
		b2Fixture* _Fixture;
		b2PolygonShape* _PolygonShape;
	
};
	
	

#endif  //_OBJECT_H_
