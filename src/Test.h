#ifndef _CAPP_H_
#define _CAPP_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <time.h>

#include "Global.h"
#include "Object.h"
#include "ObjectManager.h"
#include "RandomGen.h"


class Test{
	private:
		static bool Running;

		static sf::RenderWindow Window;

		static b2Vec2* Gravity;
		static b2World* World;
		static b2Body* Ground;
		static ObjectManager* ObjMgr;

	public:
		static int Execute();
    static void CreateBox(float w, float h, float x, float y);	
    static void CreateGround(float X, float Y);

	private:
		static bool Init();
		static void EventHandler();
		static void Process();
		static void Render();
		static void Clean();
};

#endif //_CAPP_H_
