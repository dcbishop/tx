#ifndef TX_CONTAINER_HPP
#define TX_CONTAINER_HPP

#include <vector>
#include <map>
using namespace std;

#include "Tagged.hpp"

class Contained;
class Area;
class Object;
class RigidBody;
class Creature;

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

		virtual ChildrenIterator getFirstChild();
		virtual ChildrenIterator getChildEnd();

		Object* getObjectByTag(const string tag);
		Area* getAreaByTag(const string tag);
		Creature* getCreatureByTag(const string tag);

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
class Contained {
	private:
		Container* parent_;
		
	public:
		Contained(): parent_(NULL){}
		virtual void setParent(Container* parent);
		Container* getParent();
};

#endif /* TX_CONTAINER_HPP */
