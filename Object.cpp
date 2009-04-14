#include "Object.hpp"

#include <GL/gl.h>

#include "console.h"

/**
 * The constructor. Sets cordinates to 0,0,0.
 * @param tag The Objects tag.
 * @param model The Objects RCBC model pointer.
 */
Object::Object(string tag, Model* model) {
	setTag(tag);
	
	model_ = NULL;
	setX(0.0f);
	setY(0.0f);
	setZ(0.0f);
	
	setRotX(0.0f);
	setRotY(1.0f);
	setRotZ(0.0f);
	setRotAngle(0.0f);

	area_ = NULL;
}

#warning ['TODO']: Use this function or kill it...
Object::~Object() {
}

/**
 * Renders the object to screen using RCBC.
 */
void Object::Draw() {
	if(model_ == NULL) {
		return;
	}

	glPushMatrix();
	glTranslatef(getX(), getY(), getZ());
	glRotatef(getRotAngle(), getRotX(), getRotY(), getRotZ());
	RCBC_Render(model_);
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
	x_ = x;
	y_ = y;
	z_ = z;
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
	x_ = x;
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
	z_ = z;
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
	return x_;
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
	return z_;
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
 * Sets the object's RCBC model.
 * @param model The RCBC model.
 * @see getModel()
 */
void Object::setModel(const Model& model) {
	model_ = &model;
}

/**
 * Puts the object in an area.
 * @see getArea()
 */
void Object::setArea(Area& area) {
	DEBUG_M("Entering function...");
	if(area_) {
		DEBUG_H("removing...");
		area_->removeObject(*this);
	}
	
	area_ = &area;
}

/**
 * Returns the object's area.
 * @see setArea()
 * @return The area contining the object.
 */
Area* Object::getArea() {
	return area_;
}

/**
 * Returns the object's RCBC model.
 * @see setModel()
 * @return The RCBC model.
 */
const Model& Object::getModel() {
	return *model_;
}
