#include "Container.hpp"

#include "Area.hpp"
#include "Object.hpp"
#include "RigidBody.hpp"
#include "Creature.hpp"
#include "console.h"
/**
 * Adds a thing to the container.
 * @param child The thing to be contained.
 */
void Container::addChild(Contained* child) {
	DEBUG_M("Entering function addChild...");
	if(!child) {
		DEBUG_H("\tNo child...");
		return;
	}

	// Stop adding the child more than once
	ChildrenIterator found = find(getChildBegin(), getChildEnd(), child);
	if(found != getChildEnd()) {
		DEBUG_H("\tChild alread in list...");
		return;
	}

	DEBUG_H("Child adding to list...");
	child->setParent(this);
	children_.push_back(child);

	//DEBUG_H("Child adding to list...");
	Tagged* tagged = dynamic_cast<Tagged*>(child);
	if(!tagged) {
		return;
	}

	tags_.insert(ChildrenTagPair(tagged->getTag(), tagged));
}

/**
 * Removes a thing from the container.
 * @param child The thing to be contained.
 */
void Container::removeChild(Contained* child) {
	DEBUG_M("Entering function removeChild...");
	if(!child) {
		return;
	}

	DEBUG_H("\tRemoving object from container object vector.");
	ChildrenIterator found = find(getChildBegin(), getChildEnd(), child);
	//while((found = find(getChildBegin(), getChildEnd(), child)) != getChildEnd()) {
		if(found != getChildEnd()) {
			//Object* object = dynamic_cast<Object*>(*found);

			if(*found && ((*found) == child)) {
				//DEBUG_H("\t\tFound '%s'... Removing...", object->getTag().c_str());
				children_.erase(found);
			}
		}
	//}

	DEBUG_H("\tRemoving object from container tag list.");
	ChildrenTagIterator iter = tags_.begin();
	while(iter != tags_.end()) {
		Contained* contained = dynamic_cast<Object*>(iter->second);
		if(contained  && contained == child) {
			//DEBUG_H("\t\tFound '%s'... Removing...", object->getTag().c_str());
			tags_.erase(iter);
			iter = tags_.begin();
		} else {
			iter++;
		}
	}

	DEBUG_H("\tExiting function...");
	#warning ['TODO']: This...
}

/**
 * Returns a pointer to the vector containing the children.
 */
ChildrenIterator Container::getChildBegin() {
	return children_.begin();
}

/**
 * Returns a pointer to the vector end.
 */
ChildrenIterator Container::getChildEnd() {
	return children_.end();
}

/**
 * Finds a Tagged object based on its tag id.
 * @param string The tag of the object.
 * @return The Tagged object if found or NULL.
 */
Tagged* Container::getTaggedByTag_(const string tag) {
	DEBUG_V("Entering function getTaggedByTag_...");
	ChildrenTagIterator iter = tags_.find(tag);
	if(iter != tags_.end()) {
		return iter->second;
	}
	return NULL;
}

/**
 * Gets the area based on the tag name.
 * @param tag The Area's tag.
 * @return The area pointer if found, otherwise NULL.
 */
Area* Container::getAreaByTag(const string tag) {
	#warning ['TODO']: Probabbly faster to get this from Area list...
	DEBUG_V("Entering function getAreaByTag...");
	return dynamic_cast<Area*>(getTaggedByTag_(tag));
}

/**
 * Get object by tag
 * @param tag The Objects's tag.
 * @return The Object pointer if found, otherwise NULL
 */
Object* Container::getObjectByTag(const string tag) {
	DEBUG_V("Entering function getObjectByTag...");
	return dynamic_cast<Object*>(getTaggedByTag_(tag));
}

/**
 * Get creature by tag
 * @param tag The Creature's tag.
 * @return The Object pointer if found, otherwise NULL
 */
Creature* Container::getCreatureByTag(const string tag) {
	DEBUG_V("Entering function getCreatureByTag...");
	return dynamic_cast<Creature*>(getTaggedByTag_(tag));
}

Object* Container::getNearestObjectTo(Location& location) {
	return getNearestObjectByTag(location, "");
}

Object* Container::getNearestObjectByTag(Location& location, const string tag) {
	Object* closest = NULL;
	for(ChildrenIterator iter = getChildBegin(); iter != getChildEnd(); iter++) {
		Object* object = dynamic_cast<Object*>(*iter);
		if(!object) {
			continue;
		}

		if(tag == "" || tag ==object->getTag()) {
			if(closest == NULL) {
				closest = object;
			}

			if(object->getDistanceTo(location) < closest->getDistanceTo(location)) {
				closest = object;
			}
		}
	}
	return closest;
}

/**
 * Sets the parent/owner Container.
 * @param parent The thing within which this thing is contained.
 */
void Contained::setParent(Container* parent) {
	parent_ = parent;
}

/**
 * Gets the parent/owning Container of the thing.
 * @return Pointer to the parent Container.
 */
Container* Contained::getParent() {
	return parent_;
}
