#ifndef _CAPP_H_
#define _CAPP_H_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Global.h"

#include "Physics.h"

class CApp{
	private:
		static bool Running;
		

		static sf::RenderWindow Window;
		static sf::Shape Poly;
		static Physics PhyMot;//moteur physique

	public:
		static int Execute();

	private:
		static bool Init();
		static void EventHandler();
		static void Process();
		static void Render();
		static void Clean();
};

#endif //_CAPP_H_
