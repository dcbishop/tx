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
		void Update(const int time);
		void Register(Tagged& thing);
		void Deregister(Tagged& thing);
		
		Physics& getPhysics();

		Area* getAreaByTag(const string tag);
		Object* getObjectByTag(const string tag);
		Creature* getCreatureByTag(const string tag);

	private:
		Scripting scripting_;
		Physics physics_;
		vector<Area*> areas_;
		multimap<string, Tagged*> tags_;
};
