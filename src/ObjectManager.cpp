#include "ObjectManager.h"

ObjectManager::ObjectManager(sf::RenderWindow* window, b2World* world)
{
	this->Window = window;
	this->World = world;
}

ObjectManager::~ObjectManager()
{
}

bool ObjectManager::CreateObject(const std::vector<b2Vec2>& points,float x,float y ObjectType type=Brick)
{
	if(type==Brick)
		this->ObjectList.push_back(new Brick(points));
	
	this->ObjectList.back().SetBody( this->World->CreateBody( this->ObjectList.back().GetBodyDef() ) );

	return true;
}


bool ObjectManager::CreateRectangle(float w, float h,float x,float y, ObjectType type=Brick){
	boost::ptr_vector<b2Vec2> points;
	//counter clockwise
	points.push_back(new b2Vec2(-w/2,-h/2));
	points.push_back(new b2Vec2(-w/2,h/2));
	points.push_back(new b2Vec2(w/2,h/2));
	points.push_back(new b2Vec2(w/2,-h/2) ); 
	return this->CreateObject(&points, x,y,type);
}
