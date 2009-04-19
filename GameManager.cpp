#include "GameManager.hpp"

/**
 * Update physics, everything with a tag (Areas, Objects).
 */
void GameManager::Update(const int time) {	
	for(multimap<string, Tagged*>::iterator iter = tags_.begin(); iter != tags_.end(); ++iter) {
		Updateable *u = dynamic_cast<Updateable*>(iter->second);
		if(u) {
			u->Update(time);
		}
	}
	
	physics_.Update(time);

	Updateable::Update(time);
}

/**
 * Register something to be manager by the game manager.
 * @param thing The thing to be managed.
 */
void GameManager::Register(Tagged& thing) {
	// Add to the list of tagged Taggeds.
	tags_.insert(pair<string, Tagged*>(thing.getTag(), &thing));
	thing.setGameManager(this);
	// If its an Area, add to the list of areas.
	Area* area = dynamic_cast<Area*>(&thing);
	if(area) {
		areas_.push_back(area);
		addChild(area);
	}
}

/**
 * Removes a object from the GameManager registery.
 * @param thing The thing to remove.
 */
void GameManager::Deregister(Tagged& thing) {
	#warning ['TODO']: Deregister objects...
}

/** 
 * @return Refrence to the Physics engine.
 */
Physics& GameManager::getPhysics() {
	return physics_;
}

/**
 * @return Refrence to the Scripting engine.
 */
Scripting& GameManager::getScripting() {
	return scripting_;
}

/**
 * Finds a Tagged object based on its tag id.
 * @param string The tag of the object.
 * @return The Tagged object if found or NULL.
 */
Tagged* GameManager::getTaggedByTag_(const string tag) {
	multimap<string, Tagged*>::iterator iter = tags_.find(tag);
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
Area* GameManager::getAreaByTag(const string tag) {
	#warning ['TODO']: Probabbly faster to get this from Area list...
	return dynamic_cast<Area*>(getTaggedByTag_(tag));
}

/**
 * Get object by tag
 * @param tag The Objects's tag.
 * @return The Object pointer if found, otherwise NULL
 */
Object* GameManager::getObjectByTag(const string tag) {
	return dynamic_cast<Object*>(getTaggedByTag_(tag));
}

/**
 * Get creature by tag
 * @param tag The Creature's tag.
 * @return The Object pointer if found, otherwise NULL
 */
Creature* GameManager::getCreatureByTag(const string tag) {
	return dynamic_cast<Creature*>(getTaggedByTag_(tag));
}
