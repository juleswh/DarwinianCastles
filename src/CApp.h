#ifndef _CAPP_H_
#define _CAPP_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "Global.h"
#include "Physics.h"



class CApp{
	private:
		static bool Running;
		

		static sf::RenderWindow Window;
		static sf::Shape Poly;
		static Physics PhyEng;//moteur physique

    static std::list<b2Body*> physicsObjectList; //list of pointers to the physics bodies

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
