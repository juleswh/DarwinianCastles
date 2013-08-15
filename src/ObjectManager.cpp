#include "ObjectManager.h"
using namespace std;
ObjectManager::ObjectManager(sf::RenderWindow* window, b2World* world)
{
	this->Window = window;
	this->World = world;
}

ObjectManager::~ObjectManager()
{
	for (size_t i=0 ; i<this->ObjectList.size() ; i++ ){
		this->World->DestroyBody(this->ObjectList[i]->GetBody());
	}
	this->ObjectList.clear();

}

void ObjectManager::ProcessStep()
{
	this->World->Step(STEP,8,3);
}

void ObjectManager::Render(){
	Object* obj = NULL;
	for ( size_t i = 0 ; i < this->ObjectList.size() ; i++ ){ 
		obj = this->ObjectList[i];
		obj->Refresh();
		this->Window->Draw(*obj->GetSfmlShape());
	}
}

bool ObjectManager::CreateObject(const std::vector<b2Vec2>& points,float x,float y, ObjectManager::ObjectType type)
{
	if(type==BRICK)
		this->ObjectList.push_back(new Object(points,x,y));

	this->ObjectList.back()->SetBody( this->World->CreateBody( this->ObjectList.back()->GetBodyDef() ) );

	return true;
}


bool ObjectManager::CreateRectangle(float w, float h,float x,float y, ObjectType type){
	std::vector<b2Vec2> points(4);
	//counter clockwise
	points[0].Set(-w/2,-h/2);
	points[1].Set(w/2,-h/2);
	points[2].Set(w/2,h/2);
	points[3].Set(-w/2,h/2); 

	return this->CreateObject(points, x,y,type);
}

bool ObjectManager::AddObject(Object* obj){
	this->ObjectList.push_back(obj);
	this->ObjectList.back()->SetBody( this->World->CreateBody (this->ObjectList.back()->GetBodyDef() ) );
	return true;
}


void ObjectManager::Reset(){
}
