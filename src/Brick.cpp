#include "Brick.h"

Brick::Brick(float w,float h,float x,float y,float rotation, float density,float friction){
	
	x=x;
	y=y;
	w=w;
	h=h;
	rotation=rotation;
	density=density;
	friction=friction;
	
	BodyInWorld = NULL;
}

void Brick::AddToWorld(b2World* world){
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(x,y);
	bodyDef.angle = rotation;
	bodyDef.type=b2_dynamicBody;
	BodyInWorld = world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(w,h);
	b2FixtureDef fxtDef;
	fxtDef.density=density;
	fxtDef.friction=friction;
	fxtDef.shape=&shape;
	BodyInWorld->CreateFixture(&fxtDef);
}
