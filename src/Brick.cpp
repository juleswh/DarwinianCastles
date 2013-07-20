#include "Brick.h"

Brick::Brick(float w,float h,float x,float y,float rotation, float density,float friction){
	
	this->X=x;
	this->Y=y;
	this->W=w;
	this->H=h;
	this->Rotation=rotation;
	this->Density=density;
	this->Friction=friction;
	
	this->BodyInWorld = NULL;
}

sf::Shape Brick::GetSfmlShape()
{
	sf::Shape shape;

	
	switch (this->BodyInWorld->GetFixtureList()->GetType()){
		case b2Shape::e_polygon: {
			b2PolygonShape* poly = static_cast<b2PolygonShape*>(this->BodyInWorld->GetFixtureList()->GetShape());
			for (int32 i=0; i<poly->GetVertexCount(); i++){
				shape.AddPoint(poly->GetVertex(i).x * SCALE , poly->GetVertex(i).y* SCALE ,sf::Color(0, 0, 0),     sf::Color(128, 128, 128) );
			}
			shape.SetPosition(this->BodyInWorld->GetPosition().x * SCALE, this->BodyInWorld->GetPosition().y * SCALE);
			shape.SetRotation(-180/b2_pi * this->BodyInWorld->GetAngle());
			shape.EnableOutline(true);
			shape.EnableFill(false);
			shape.SetOutlineWidth(1);
	
			break;
		}
		default:
			break;
	}

	return shape;
}
	

void Brick::AddToWorld(b2World* world){
	//creates the body def
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(this->X,this->Y);
	bodyDef.angle = this->Rotation;
	bodyDef.type=b2_dynamicBody;
	//adds the body to the world
	this->BodyInWorld = world->CreateBody(&bodyDef);

	//defines the fixture of the body
	b2PolygonShape shape;
	shape.SetAsBox(this->W,this->H);
	b2FixtureDef fxtDef;
	fxtDef.density=this->Density;
	fxtDef.friction=this->Friction;
	fxtDef.shape=&shape;
	//attach it to the body in the world
	this->BodyInWorld->CreateFixture(&fxtDef);
}
