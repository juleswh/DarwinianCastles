#include "Physics.h"

Physics::Physics()
{

	//init the world
	this->Gravity = new b2Vec2(0.f, 9.8f);
	this->World = new b2World(*this->Gravity);
	this->CreateGround(0.f, 25.f);
}

void Physics::Process(float step){
	this->World->Step(step,8,3);
	/*std::cout << "step" << std::endl;
	for (b2Body* bite =World->GetBodyList(); bite !=0 ; bite = bite->GetNext()){
		std::cout << bite->GetType() << std::endl;
		std::cout << bite->GetPosition().x << ' ' << bite->GetPosition().y << std::endl;
	}*/
}

void Physics::CreateGround(float x,float y){
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(x,y);
	BodyDef.type=b2_staticBody;
	b2Body* Body = this->World->CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((800.0f)/30,(16.f/2)/30);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}

void Physics::CreateBox(float w,float h,float x,float y){
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(x,y);
	bodyDef.type=b2_dynamicBody;
	b2Body* body = this->World->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(w,h);
	b2FixtureDef fxtDef;
	fxtDef.density=2.f;
	fxtDef.friction=0.7f;
	fxtDef.shape=&shape;
	body->CreateFixture(&fxtDef);
}
