#ifndef _OBJECT_H_
#define _OBJECT_H_


#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Global.h"


class Object{
	public:

		enum ObjectType {BRICK=1, BULLET, HEART};

		Object(const std::vector<b2Vec2>& vertices,float x, float y, float rotation=0.f, float friction=0.3f,float density=1.0f);
		virtual ~Object();

		void Refresh();

	public:
		void SetBody(b2Body* body);
		b2Body* GetBody();

		void SetBodyDef(b2BodyDef* bodyDef);
		b2BodyDef* GetBodyDef();

		void SetPolygonShape(b2PolygonShape* polygonShape);
		
		void SetFixtureDef(b2FixtureDef* fixtDef);

		sf::Shape* GetSfmlShape();

	private:
		b2BodyDef* _BodyDef;
		b2Body* _Body;
		b2FixtureDef* _FixtureDef;
		b2Fixture* _Fixture;
		b2PolygonShape* _PolygonShape;
		sf::Shape* _SfmlShape;
	
};
	
	

#endif  //_OBJECT_H_
