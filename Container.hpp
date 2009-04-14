#ifndef TX_CONTAINER_HPP
#define TX_CONTAINER_HPP

#include <vector>
using namespace std;

#include "Tagged.hpp"

class Contained;

/**
 * An abstract class for things that can contain or own things.
 * Useabble for maps having objects, inventories with items, etc...
 */
class Container {
	public:
		void addChild(Contained* child);
	private:
		vector<Contained*> children_;
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
		void setParent(Container* parent);
		Container* getParent();
};

#endif
