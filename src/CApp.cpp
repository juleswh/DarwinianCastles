#include "CApp.h"

#define STD_W 0.6f
#define STD_H 0.6f

using namespace std;

bool CApp::Running=true;
sf::Shape CApp::Poly;
sf::RenderWindow CApp::Window;
Physics CApp::PhyMot;

int CApp::Execute()
{
	CApp::Init();
	int nite=0;
	while (CApp::Running)
	{
		nite++;
		EventHandler();
		Process();
		Render();
	}

	return EXIT_SUCCESS;
}

bool CApp::Init(){
	sf::WindowSettings settings;
	settings.AntialiasingLevel = 8;
	Window.Create(sf::VideoMode(800,600,32),"SFML Graphics",sf::Style::Close,settings);
	Window.SetFramerateLimit(60);
	PhyMot.CreateGround(0.f,19.f);
	return true;
}

void CApp::EventHandler(){
	sf::Event Event;
	float random_w,random_h;
	while(Window.GetEvent(Event)){
		switch(Event.Type){
			case sf::Event::Closed :
				Running=false;
				break;
			case sf::Event::MouseButtonReleased:
				random_w = (rand() % 1000) / 1000.0;
				random_h = (rand() % 1000 )/ 1000.0;
				PhyMot.CreateBox(random_w,random_h,Event.MouseButton.X/SCALE,Event.MouseButton.Y/SCALE);
				//shape = sf::Shape::Rectangle(-30,-30,30,30,sf::Color::Black,0,sf::Color::Black);
				//shape.SetPosition(Event.MouseButton.X,Event.MouseButton.Y);
				//shape.EnableOutline(true);
				break;
      case sf::Event::KeyPressed:
        if (Event.Key.Code == sf::Key::Escape) {
          Running = false;
        }
        break;
			default:
				break;
		}
	}
}

void CApp::Process(){
	PhyMot.Process(STEP);
}

void CApp::Render(){
  b2Fixture * fite = NULL;
  sf::Shape * shape = NULL;
  b2PolygonShape * poly = NULL;

	Window.Clear(sf::Color::White);
	for (b2Body* bite = PhyMot.World->GetBodyList(); bite != NULL; bite = bite->GetNext()){
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
						Window.Draw(*shape);
            delete shape;
						break;

					default:
            break;
				}
		}else{
			sf::Shape shape = sf::Shape::Rectangle(0,0,200,10,sf::Color::Black,0.0f,sf::Color::Black);
			shape.SetPosition(bite->GetPosition().x *SCALE, bite->GetPosition().y * SCALE);
			Window.Draw(shape);
		}
	}

	Window.Display();
}

int main(){
	return CApp::Execute();	
}
