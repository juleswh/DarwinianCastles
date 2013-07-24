#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

#include <Box2D/Box2D.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Global.h"

#include "Physics.h"
#include "Object.h"

using std::vector;

//the unit used is Box2D unit : meters -> NOT PIXELS
class ObjectManager {

	public:
		
		//types of object we manage
		enum ObjectType {Brick=1, Bullet, Heart};

		//Constructor
		ObjectManger(sf::RenderWindow* window, Physics* physicsEngine);
		//destructor
		virtual ~ObjectManager();

	private:
		sf::RenderingWindow* Window;
		b2World* World;
		
		boost::ptr_vector<Object> ObjectList;

	public:
		//process a Box2d step, and render the result into sfml window
		//do clear window
		void ProcessStep(void);
	
		/** defines an Object from given points
		 	* one point -> circle which radius is of the given b2vec2 length
			* two points -> edge
			* three+ points -> polygon
		 **/
		bool CreateObject(const std::vector<b2Vec2>& points, unsigned int numberOfPoints, ObjectType type=Brick );
		bool CreateRectangle(float w, float h,float x,float y, ObjectType type=Brick);
		
		//resets the world : destroys all objects
		void Reset();
		
		
	
};


#endif // _OBJECT_MANAGER_H_ 
