#include "GameManager.hpp"

GameManager::GameManager() {
	luabind::globals(scripting_.getLuaState())["gm"] = this;
}

/**
 * update physics, everything with a tag (Areas, Objects).
 */
void GameManager::update(const int time) {	
	for(multimap<string, Tagged*>::iterator iter = tags_.begin(); iter != tags_.end(); ++iter) {
		Updateable *u = dynamic_cast<Updateable*>(iter->second);
		if(u) {
			u->update(time);
		}
	}

	physics_.update(time);

	Updateable::update(time);
}

/**
 * registerObject something to be manager by the game manager.
 * @param thing The thing to be managed.
 */
void GameManager::registerObject(Tagged& thing) {
	// Add to the list of tagged Taggeds.
	//tags_.insert(pair<string, Tagged*>(thing.getTag(), &thing));
	//thing.setGameManager(this);

	Contained* contained = dynamic_cast<Contained*>(&thing);
	if(contained) {
		addChild(contained);
	}

	thing.setGameManager(this);

	// If its an Area, add to the list of areas.
	Area* area = dynamic_cast<Area*>(&thing);
	if(area) {
		areas_.push_back(area);
	}
}

/**
 * Removes a object from the GameManager registerObjecty.
 * @param thing The thing to remove.
 */
void GameManager::deregisterObject(Tagged& thing) {
	Contained* contained = dynamic_cast<Contained*>(&thing);
	if(contained) {
		removeChild(contained);
	}
	#warning ['TODO']: deregister objects, remove areas from list...
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

