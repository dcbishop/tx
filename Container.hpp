#ifndef TX_CONTAINER_HPP
#define TX_CONTAINER_HPP

#include <vector>
#include <map>
using namespace std;

#include "Tagged.hpp"
#include "MemoryLocation.hpp"

class Contained;
class Area;
class Object;
class RigidBody;
class Creature;
class Location;

typedef vector<Contained*> ChildrenVector;
typedef ChildrenVector::iterator ChildrenIterator;
typedef multimap<string, Tagged*> ChildrenTagMap;
typedef ChildrenTagMap::iterator ChildrenTagIterator;
typedef pair<string, Tagged*> ChildrenTagPair;

/**
 * An abstract class for things that can contain or own things.
 * Useabble for maps having objects, inventories with items, etc...
 */
class Container {
	public:
		virtual void addChild(Contained* child);
		virtual void removeChild(Contained* child);
		//virtual vector<Contained*>* getChildren();

		virtual ChildrenIterator getChildBegin();
		virtual ChildrenIterator getChildEnd();

		Object* getObjectByTag(const string tag);
		RigidBody* getRigidBodyByTag(const string tag);
		Area* getAreaByTag(const string tag);
		Creature* getCreatureByTag(const string tag);
		Object* getNearestObjectTo(Location& location);
		Object* getNearestObjectByTag(Location& location, const string tag);

	protected:
		ChildrenVector children_;
		ChildrenTagMap tags_;

	private:
		Tagged* getTaggedByTag_(const string tag);

};

/**
 * An abstract class for things that can be contained or owned by other
 * things. Useabble for objects in maps, items in inventories, etc...
 */
class Contained : public MemoryLocation {
	private:
		Container* parent_;
		#warning ['TODO']: Execute Lua code to remove globals[memorylocation] to allow for future objects that share the same address to work
	public:
		Contained(): parent_(NULL){}
		virtual void setParent(Container* parent);
		Container* getParent();
};

#endif /* TX_CONTAINER_HPP */
