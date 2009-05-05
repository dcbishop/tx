#include "Object.hpp"

#include <GL/gl.h>

#include "console.h"
#include "GameManager.hpp"
#include "Interface.hpp"

/**
 * The constructor. Sets cordinates to 0,0,0.
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
	glTranslatef(-getX(), getY(), -getZ());
	glRotatef(getRotAngle(), getRotX(), getRotY(), getRotZ());
	
	//Model* model = getModel(rm);
	//RCBC_Render(model);
	visual_->draw(interface);
	
	glPopMatrix();
}

/**
 * Sets the objects X, Y, Z coordinates .
 * @param x OpenGL style X cord.
 * @param y OpenGL style Y cord.
 * @param z OpenGL style Y cord.
 * @see setPos()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 */
void Object::setPos(const float x, const float y, const float z) {
	Object::setX(x);
	Object::setY(y);
	Object::setZ(z);
}

/**
 * Sets the objects X coordinate.
 * @param x OpenGL style X cordinate.
 * @see setPos()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 */
void Object::setX(const float x) {
	x_ = -x;
}

/**
 * Sets the objects Y coordinate.
 * @param y OpenGL style Y cordinate.
 * @see setPos()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 */
void Object::setY(const float y) {
	y_ = y;
}

/**
 * Sets the objects Z coordinate.
 * @param z OpenGL style Z cordinate.
 * @see setPos()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 */
void Object::setZ(const float z) {
	z_ = -z;
}

/**
 * Returns the current X cordinate.
 * @see setPos()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @return The X cordinate in OpenGL style.
 */
const float Object::getX() {
	return -x_;
}

/**
 * Returns the current Y cordinate.
 * @see setPos()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @return The Y cordinate in OpenGL style.
 */
const float Object::getY() {
	return y_;
}

/**
 * Returns the current Z cordinate.
 * @see setPos()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @return The Z cordinate in OpenGL style.
 */
const float Object::getZ() {
	return -z_;
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @param rx the X rotation in OpenGL cordinates.
 */
void Object::setRotX(const float rx) {
	rx_ = rx;
	setRot_();
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @param ry the Y rotation in OpenGL cordinates.
 */
void Object::setRotY(const float ry) {
	ry_ = ry;
	setRot_();
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @param rz the Z rotation in OpenGL cordinates.
 */
void Object::setRotZ(const float rz) {
	rz_ = rz;
	setRot_();
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @param angle the angle of rotation in OpenGL cordinates.
 */
void Object::setRotAngle(const float angle) {
	angle_ = angle;
	setRot_();
}

void Object::setRot_() {
	if(angle_ > 360.0f || angle_ < -360.0f) {
		angle_ = fmodf(angle_, 360.0f);
	}
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @return the X rotation in OpenGL cordinates.
 */
const float Object::getRotX() {
	return rx_;
}
/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @return the Y rotation in OpenGL cordinates.
 */
const float Object::getRotY() {
	return ry_;
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @return the Z rotation in OpenGL cordinates.
 */
const float Object::getRotZ() {
	return rz_;
}

/**
 * @see getRotX()
 * @see getRotY()
 * @see getRotZ()
 * @see getRotAngle()
 * @see setRotX()
 * @see setRotY()
 * @see setRotZ()
 * @see setRotAngle()
 * @return the angle of rotation in OpenGL cordinates.
 */
const float Object::getRotAngle() {
	return angle_;
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
 * Puts the object in an area.
 * @see getArea()
 */
void Object::setArea(Area& area) {
	DEBUG_M("Entering function...");
	setParent(&area);
}

/**
 * Returns the object's area.
 * @see setArea()
 * @return The area contining the object.
 */
Area* Object::getArea() {
	return dynamic_cast<Area*>(getParent());
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
				luabind::globals(sc.getLuaState())["gm"] = getGameManager();
				sc.loadLua(scripts_[SCRIPT_ONUPDATE-1]);
				//luaL_dostring(sc.getLuaState(), "self.x = 1.0\nprint(self.x)\n");
				/*luaL_dostring(sc.getLuaState(), "print self.getX(0.0)\n");
				luaL_dostring(sc.getLuaState(), "self.setY(0.0)\n");
				luaL_dostring(sc.getLuaState(), "self.setZ(0.0)\n");*/
			}
		}
	}
	Updateable::update(time);
}
