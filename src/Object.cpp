#include "Object.h"

using namespace std;

Object::Object(const std::vector<b2Vec2>& vertices,float x, float y, float rotation, float friction,float density){
	b2BodyDef *bodyDef = new b2BodyDef();
	b2PolygonShape *polyShape = new b2PolygonShape();	
	b2FixtureDef *fixtDef = new b2FixtureDef();

	bodyDef->type=b2_dynamicBody;
	bodyDef->position.Set(x,y);
	bodyDef->angle=rotation;
	this->SetBodyDef(bodyDef);
	
	polyShape->Set(&(vertices.front()),vertices.size());
	
	this->SetPolygonShape(polyShape);

	fixtDef->shape = polyShape;
	fixtDef->density = 1.0f;
	fixtDef->friction = 0.3f;
	this->SetFixtureDef(fixtDef);

	this->_SfmlShape = new sf::Shape();
	for (size_t i = 0 ; i < vertices.size() ; i++){
		this->_SfmlShape->AddPoint(vertices[i].x * SCALE , vertices[i].y *SCALE, sf::Color(128*density, 128*density, 128*density),     sf::Color(128*friction,0,0 ) );
		this->_SfmlShape->EnableOutline(true);
		this->_SfmlShape->SetOutlineWidth(2);
	}
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

void Object::Refresh(){
	this->_SfmlShape->SetPosition(this->_Body->GetPosition().x * SCALE, this->_Body->GetPosition().y * SCALE);
	this->_SfmlShape->SetRotation(-180/b2_pi * this->_Body->GetAngle());
}

sf::Shape* Object::GetSfmlShape(){
	return this->_SfmlShape;
}
