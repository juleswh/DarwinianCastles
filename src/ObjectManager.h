#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Global.h"

#include "Object.h"

using std::vector;

//the unit used is Box2D unit : meters -> NOT PIXELS
class ObjectManager {

	public:
		enum ObjectType {BRICK=1, BULLET, HEART};
		
		//Constructor
		ObjectManager(sf::RenderWindow* window, b2World* world);
		//destructor
		virtual ~ObjectManager();

	private:
		sf::RenderWindow* Window;
		b2World* World;
		
		std::vector<Object*> ObjectList;

	public:
		//process a Box2d step
		void ProcessStep(void);
	
		/**
			* Render objects in the window
			* do not clear window
			* do not do display()
			**/
		void Render();

		/** defines an Object from given points
		 	* one point -> circle which radius is of the given b2vec2 length
			* two points -> edge
			* three+ points -> polygon
		 **/
		bool CreateObject(const std::vector<b2Vec2>& points, float x, float y, ObjectManager::ObjectType type=BRICK);
		bool CreateRectangle(float w, float h,float x,float y, ObjectType type=BRICK);
		bool AddObject(Object* obj);
		//resets the world : destroys all objects
		void Reset();
		
		
	
};


#endif // _OBJECT_MANAGER_H_ 
