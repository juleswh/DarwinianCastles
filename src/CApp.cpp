#include "CApp.h"

#define STD_W 0.6f
#define STD_H 0.6f

using namespace std;

bool CApp::Running=true;
sf::RenderWindow CApp::Window;
Physics CApp::PhyEng;
std::list<b2Body*> CApp::physicsObjectList; //list of pointers to the physics bodies

int CApp::Execute()
{
	CApp::Init();
	while (CApp::Running)
	{
    CApp::EventHandler();
    CApp::Process();
    CApp::Render();
	}

	return EXIT_SUCCESS;
}

bool CApp::Init(){
	sf::WindowSettings settings;
	settings.AntialiasingLevel = 8;
	CApp::Window.Create(sf::VideoMode(800,600,32),"SFML Graphics",sf::Style::Close,settings);
	CApp::Window.SetFramerateLimit(60);
  CApp::CreateGround(0.f,19.f);
	return true;
}

void CApp::EventHandler(){
	sf::Event Event;
	float random_w,random_h;
	while(CApp::Window.GetEvent(Event)){
		switch(Event.Type){
			case sf::Event::Closed :
				CApp::Running=false;
				break;
			case sf::Event::MouseButtonReleased:
        if (Event.MouseButton.Button == sf::Mouse::Left) {
				random_w = (rand() % 1000) / 1000.0;
				random_h = (rand() % 1000 )/ 1000.0;
				CApp::CreateBox(random_w,random_h,Event.MouseButton.X/SCALE,Event.MouseButton.Y/SCALE);
        } else if (Event.MouseButton.Button == sf::Mouse::Right) {
          if (!CApp::physicsObjectList.empty()) {
            /* remove object from world */
            CApp::PhyEng.World->DestroyBody(CApp::physicsObjectList.back());
            /* also remove pointer in list */
            CApp::physicsObjectList.pop_back();
          }
        }
				break;
      case sf::Event::KeyPressed:
        if (Event.Key.Code == sf::Key::Escape) {
          CApp::Running = false;
        }
        break;
			default:
				break;
		}
	}
}

void CApp::Process(){
	CApp::PhyEng.Process(STEP);
}

void CApp::Render(){
  b2Fixture * fite = NULL;
  sf::Shape * shape = NULL;
  b2PolygonShape * poly = NULL;

	CApp::Window.Clear(sf::Color::White);
	for (b2Body* bite = CApp::PhyEng.World->GetBodyList(); bite != NULL; bite = bite->GetNext()){
		if(bite->GetType() == b2_dynamicBody){
				fite = bite->GetFixtureList();
				switch (fite->GetType()){
					case b2Shape::e_polygon :
						poly = static_cast<b2PolygonShape*>(fite->GetShape());
            shape = new sf::Shape;
						for (int32 i=0; i<poly->GetVertexCount(); i++){
							shape->AddPoint(poly->GetVertex(i).x * SCALE , poly->GetVertex(i).y* SCALE ,sf::Color(0, 0, 0),     sf::Color(128, 128, 128) );
						}
						shape->SetPosition(bite->GetPosition().x * SCALE, bite->GetPosition().y * SCALE);
						shape->SetRotation(-180/b2_pi * bite->GetAngle());
						shape->EnableOutline(true);
						shape->EnableFill(false);
						shape->SetOutlineWidth(1);
						CApp::Window.Draw(*shape);
            delete shape;
						break;

					default:
            break;
				}
		}else{
			sf::Shape shape = sf::Shape::Rectangle(0,0,200,10,sf::Color::Black,0.0f,sf::Color::Black);
			shape.SetPosition(bite->GetPosition().x *SCALE, bite->GetPosition().y * SCALE);
			CApp::Window.Draw(shape);
		}
	}

	CApp::Window.Display();
}

void CApp::CreateGround(float x,float y){
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(x,y);
	BodyDef.type=b2_staticBody;
	b2Body* Body = CApp::PhyEng.World->CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((800.f)/30,(16.f/2)/30);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}

void CApp::CreateBox(float w,float h,float x,float y){
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(x,y);
	bodyDef.type=b2_dynamicBody;
	b2Body* body = CApp::PhyEng.World->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(w,h);
	b2FixtureDef fxtDef;
	fxtDef.density=2.f;
	fxtDef.friction=0.7f;
	fxtDef.shape=&shape;
	body->CreateFixture(&fxtDef);
     
  CApp::physicsObjectList.push_front(body);
}

int main(){
	return CApp::Execute();	
}
