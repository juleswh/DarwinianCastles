#include "Test.h"

#define STD_W 0.6f
#define STD_H 0.6f

using namespace std;

bool Test::Running=true;
sf::RenderWindow Test::Window;
Physics Test::PhyEng;
std::vector<Object*> Test::ObjectList; //list of pointers to the physic bodies

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
  Test::CreateGround(0.f,19.f);
	return true;
}

void Test::EventHandler(){
	sf::Event Event;
	float random_w,random_h;
	while(Test::Window.GetEvent(Event)){
		switch(Event.Type){
			case sf::Event::Closed :
				Test::Running=false;
				break;
			case sf::Event::MouseButtonReleased:
        if (Event.MouseButton.Button == sf::Mouse::Left) {
				random_w = (rand() % 1000) / 1000.0;
				random_h = (rand() % 1000 )/ 1000.0;
				Test::CreateBox(random_w,random_h,Event.MouseButton.X/SCALE,Event.MouseButton.Y/SCALE);
        } else if (Event.MouseButton.Button == sf::Mouse::Right) {
          if (!Test::ObjectList.empty()) {
            /* remove object from world */
            Test::PhyEng.World->DestroyBody(Test::ObjectList.back()->GetBody());
            /* also remove pointer in list */
						delete Test::ObjectList.back();
            Test::ObjectList.pop_back();
          }
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
	Test::PhyEng.Process(STEP);
}

void Test::Render(){
  b2Fixture * fite = NULL;
  sf::Shape * shape = NULL;
  b2PolygonShape * poly = NULL;

	Test::Window.Clear(sf::Color::White);
	for (b2Body* bite = Test::PhyEng.World->GetBodyList(); bite != NULL; bite = bite->GetNext()){
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
						Test::Window.Draw(*shape);
            delete shape;
						break;

					default:
            break;
				}
		}else{
			sf::Shape shape = sf::Shape::Rectangle(0,0,800,10,sf::Color::Black,0.0f,sf::Color::Black);
			shape.SetPosition(bite->GetPosition().x *SCALE, bite->GetPosition().y * SCALE);
			Test::Window.Draw(shape);
		}
	}

	Test::Window.Display();
}

void Test::CreateGround(float x,float y){
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(x,y);
	BodyDef.type=b2_staticBody;
	b2Body* Body = Test::PhyEng.World->CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((800.f)/30,(16.f/2)/30);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}

void Test::CreateBox(float w,float h,float x,float y){
	std::vector<b2Vec2> points(4);
	//counter clockwise
	//points.push_back(new b2Vec2(-w/2,-h/2));
	//points.push_back(new b2Vec2(-w/2,h/2));
	//points.push_back(new b2Vec2(w/2,h/2));
	//points.push_back(new b2Vec2(w/2,-h/2) ); 

	points[0].Set(-w/2,-h/2);
	points[1].Set(w/2,-h/2);
	points[2].Set(w/2,h/2);
	points[3].Set(-w/2,h/2); 

  Test::ObjectList.push_back(new Object(points,x,y));
	Test::ObjectList.back()->SetBody(Test::PhyEng.World->CreateBody(Test::ObjectList.back()->GetBodyDef()));
}

void Test::Clean(){
	for (int i=0 ; i < Test::ObjectList.size() ; i++ ){
		Test::PhyEng.World->DestroyBody(Test::ObjectList[i]->GetBody());
		delete Test::ObjectList[i];
	}
	Test::ObjectList.clear();
}
int main(){
	return Test::Execute();	
}
