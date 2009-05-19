#ifndef TX_GAMEMANAGER_HPP
#define TX_GAMEMANAGER_HPP


#include <vector>
#include <map>

using namespace std;

#include "Updateable.hpp"
#include "Tagged.hpp"
#include "Container.hpp"
#include "Scripting.hpp"
#include "Physics.hpp"
#include "Creature.hpp"
#include "Area.hpp"

/**
 * A class that is responsible for all the ingame stuff.
 * Doesn't handle the rendering.
 */
class GameManager : public Updateable, public Container {
	public:
		GameManager();
		void update(const int time);
		void registerObject(Tagged& thing);
		void deregisterObject(Tagged& thing);
		
		Physics& getPhysics();
		Scripting& getScripting();
		
		int getGameTime();


		/*Area* getAreaByTag(const string tag);
		Object* getObjectByTag(const string tag);
		Creature* getCreatureByTag(const string tag);*/

	private:
		Tagged* getTaggedByTag_(const string tag);
		Scripting scripting_;
		Physics physics_;
		vector<Area*> areas_;
		//multimap<string, Tagged*> tags_;
};

#endif /* TX_GAMEMANAGER_HPP */
