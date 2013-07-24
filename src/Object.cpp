#include "Object.h"

using namespace std;

Object::Object(const std::vector<b2Vec2>& vertices,float x, float y){
	b2BodyDef *bodyDef = new b2BodyDef();
	b2PolygonShape *polyShape = new b2PolygonShape();	
	b2FixtureDef *fixtDef = new b2FixtureDef();

	bodyDef->type=b2_dynamicBody;
	bodyDef->position.Set(x,y);
	this->SetBodyDef(bodyDef);
	
//	polyShape->SetAsBox(1.,1.);
	
	polyShape->Set(&(vertices.front()),vertices.size());
	
	this->SetPolygonShape(polyShape);

	fixtDef->shape = polyShape;
	fixtDef->density = 1.0f;
	fixtDef->friction = 0.3f;
	this->SetFixtureDef(fixtDef);
}

Object::~Object(){
	delete this->_PolygonShape;
	delete this->_FixtureDef;
	delete this->_BodyDef;
}


void Object::SetBody(b2Body* body){

	this->_Body = body;
	this->_Fixture = this->_Body->CreateFixture(this->_FixtureDef);
}


b2Body* Object::GetBody(){
	return this->_Body;
}

void Object::SetPolygonShape(b2PolygonShape* polygonShape){
	this->_PolygonShape = polygonShape;
}


void Object::SetBodyDef(b2BodyDef* bodyDef){
	this->_BodyDef = bodyDef;
}

b2BodyDef* Object::GetBodyDef(){
	return this->_BodyDef;
}

void Object::SetFixtureDef(b2FixtureDef* fixtDef){
	this->_FixtureDef = fixtDef;
}
