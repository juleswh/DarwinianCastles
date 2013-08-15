#include "Test.h"

#define STD_W 0.6f
#define STD_H 0.6f

using namespace std;

bool Test::Running=true;
sf::RenderWindow Test::Window;
b2Vec2* Test::Gravity;
b2World* Test::World;
ObjectManager* Test::ObjMgr;
b2Body* Test::Ground;


int Test::Execute()
{
	Test::Init();
	while (Test::Running)
	{
    Test::EventHandler();
    Test::Process();
    Test::Render();
	}
	Test::Clean();

	return EXIT_SUCCESS;
}

bool Test::Init(){
	sf::WindowSettings settings;
	settings.AntialiasingLevel = 8;
	Test::Window.Create(sf::VideoMode(800,600,32),"SFML Graphics",sf::Style::Close,settings);
	Test::Window.SetFramerateLimit(60);

	Test::Gravity = new b2Vec2(0.f, 9.8f);
	Test::World = new b2World(*Test::Gravity);
	Test::ObjMgr = new ObjectManager(&Test::Window,Test::World);
  Test::CreateGround(-10,600/SCALE-3);
	srand(time(0));
	return true;
}

void Test::EventHandler(){
	sf::Event Event;
	//float random_w,random_h,random_friction,random_density;
	while(Test::Window.GetEvent(Event)){
		switch(Event.Type){
			case sf::Event::Closed :
				Test::Running=false;
				break;
			case sf::Event::MouseButtonReleased:
        if (Event.MouseButton.Button == sf::Mouse::Left) {
					/*random_w = (rand() % 5000) / 1000.0;
					random_h = (rand() % 5000 )/ 1000.0;
					random_friction = (rand() % 1000 )/ 1000.0;
					random_density = (rand() % 1000 )/ 1000.0;
					Test::ObjMgr->CreateRectangle(random_w,random_h,Event.MouseButton.X/SCALE,Event.MouseButton.Y/SCALE);
					 */
					ObjMgr->AddObject(RandomGen::RandGenerate());
        } else if (Event.MouseButton.Button == sf::Mouse::Right) {
            /* remove object from world */
            /* also remove pointer in list */
        }
				break;
      case sf::Event::KeyPressed:
        if (Event.Key.Code == sf::Key::Escape) {
          Test::Running = false;
        }
        break;
			default:
				break;
		}
	}
}

void Test::Process(){
	Test::ObjMgr->ProcessStep();
}

void Test::Render(){
	Test::Window.Clear(sf::Color::White);
	Test::ObjMgr->Render();


	//draw the ground
	sf::Shape shape = sf::Shape::Rectangle(0,0,1600,1,sf::Color::Black,0.0f,sf::Color::Black);
	shape.SetPosition(Test::Ground->GetPosition().x *SCALE - 10, Test::Ground->GetPosition().y * SCALE);
	Test::Window.Draw(shape);

	Test::Window.Display();
}

void Test::CreateGround(float x,float y){
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(x,y);
	BodyDef.type=b2_staticBody;
	Test::Ground = Test::World->CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((800.f*2)/SCALE,0.5);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Test::Ground->CreateFixture(&FixtureDef);
}

void Test::Clean(){
	Test::ObjMgr->Reset();
}

int main(){
	return Test::Execute();	
}
