#include "Physics.h"

Physics::Physics()
{

	//init the world
	this->Gravity = new b2Vec2(0.f, 9.8f);
	this->World = new b2World(*this->Gravity);
}

void Physics::Process(float step){
	this->World->Step(step,8,3);
	/*std::cout << "step" << std::endl;
	for (b2Body* bite =World->GetBodyList(); bite !=0 ; bite = bite->GetNext()){
		std::cout << bite->GetType() << std::endl;
		std::cout << bite->GetPosition().x << ' ' << bite->GetPosition().y << std::endl;
	}*/
}
