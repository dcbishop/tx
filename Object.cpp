#include "Object.hpp"

#include <GL/gl.h>

#include "console.h"
#include "GameManager.hpp"
#include "Interface.hpp"

/**
 * The constructor. Sets coordinates to 0,0,0.
 * @param tag The Objects tag.
 * @param model The Objects RCBC model pointer.
 */
Object::Object(string tag, Visual* model) {
	setTag(tag);

	visual_ = model;
	setX(0.0f);
	setY(0.0f);
	setZ(0.0f);

	setRotX(0.0f);
	setRotY(1.0f);
	setRotZ(0.0f);
	setRotAngle(0.0f);

	for(int i = 0; i < NUM_SCRIPTS; i++) {
		scripts_[i] = "";
	}
}

#warning ['TODO']: Use this function or kill it...
Object::~Object() {
	DEBUG_M("Entering function...");
	Area* area = getArea();
	if(area) {
		DEBUG_H("calling area->removeChild...");
		area->removeChild(this);
	}
	GameManager* gm = getGameManager();
	if(gm) {
		DEBUG_H("calling gm->removeChild...");
		gm->removeChild(this);
	}
	DEBUG_H("Exiting function...");
}

/**
 * Renders the object to screen using RCBC.
 * @param rm The resource manager.
 */
void Object::draw(Interface* interface) {
	ResourceManager* rm = interface->getResourceManager();
	if(!visual_ || !rm || !isVisible()) {
		return;
	}

	glPushMatrix();
	glTranslatef(getX(), getY(), getZ());
	glRotatef(getRotAngle(), getRotX(), getRotY(), getRotZ());

	//visual_->preDraw(interface);
	visual_->draw(interface);
	//visual_->postDraw(interface);

	glPopMatrix();
}

/**
 * Sets the object's visual information.
 * @param visual The visual information.
 * @see getVisual()
 */
void Object::setVisual(Visual& visual) {
	visual_ = &visual;
}

/**
 * Returns the object's visual information.
 * @see setVisual()
 * @return The the visual informaion.
 */
Visual& Object::getVisual() {
	return *visual_;
}



/**
 * Sets the LUA script.
 * @param type The type of script to set (eg. SCRIPT_ONupdate).
 * @param filename The filename of the script.
 */
void Object::setScript(const int type, const string filename) {
	if(type < 1 || type > NUM_SCRIPTS) {
		return;
	}
	scripts_[type-1] = filename;
}

/**
 * Gets the LUA script filename.
 * @param type The type of script to get.
 */
string Object::getScript(const int type) {
	if(type < 1 || type > NUM_SCRIPTS) {
		return "";
	}
	return scripts_[type-1];
}

/**
 * updates the object and fires any onupdate script it has.
 * @param time The current game time.
 */
void Object::update(const int time) {
	if(scripts_[SCRIPT_ONUPDATE-1] != "") {
		GameManager* gm = getGameManager();
		if(gm) {
			Scripting& sc = gm->getScripting();
			if(&sc) {
				luabind::globals(sc.getLuaState())["self"] = this;
				luabind::globals(sc.getLuaState())["time"] = time;
				luabind::globals(sc.getLuaState())["addr"] = (long)this;
				sc.loadLua(scripts_[SCRIPT_ONUPDATE-1]);
			}
		}
	}
	Updateable::update(time);
}

void Object::addVfx(Vfx* vfx) {
	Visual& visual = getVisual();
	if(&visual) {
		visual.addVfx(vfx);
	}
}
