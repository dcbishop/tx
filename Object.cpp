#include "Object.hpp"

#include <GL/gl.h>

#include "console.h"

Object::Object() {
	model_ = NULL;
	setX(1.0f);
	setY(0.0f);
	setZ(0.0f);
	
	setRotX(0.0f);
	setRotY(1.0f);
	setRotZ(0.0f);
	setRotAngle(0.0f);

#warning ['TODO']: This shoud be the current time...
	last_update_ = 0;
	area_ = NULL;
}

#warning ['TODO']: Use this of kill it...
Object::~Object() {
}

void Object::Draw() {
	if(!model_) {
		return;
	}

	glPushMatrix();
	glTranslatef(getX(), getY(), getZ());
	glRotatef(getRotAngle(), getRotX(), getRotY(), getRotZ());
	RCBC_Render(model_);
	glPopMatrix();
}

void Object::Update(const int time) {
	last_update_ = time;
}

void Object::setPos(const float x, const float y, const float z) {
	x_ = x;
	y_ = y;
	z_ = z;
}

void Object::setX(const float x) {
	x_ = x;
}

void Object::setY(const float y) {
	y_ = y;
}

void Object::setZ(const float z) {
	z_ = z;
}

const float Object::getX() {
	return x_;
}

const float Object::getY() {
	return y_;
}

const float Object::getZ() {
	return z_;
}

void Object::setRotX(const float rx) {
	rx_ = rx;
}

void Object::setRotY(const float ry) {
	ry_ = ry;
}

void Object::setRotZ(const float rz) {
	rz_ = rz;
}

void Object::setRotAngle(const float angle) {
	angle_ = angle;
}

const float Object::getRotX() {
	return rx_;
}

const float Object::getRotY() {
	return ry_;
}

const float Object::getRotZ() {
	return rz_;
}

const float Object::getRotAngle() {
	return angle_;
}

const float Object::getLastUpdate() {
	return last_update_;
}

void Object::setModel(const Model* model) {
	model_ = model;
}

void Object::setArea(Area* area) {
	DEBUG_M("Entering function...");
	if(area_) {
		DEBUG_H("removing...");
		area_->removeObject(this);
	}
	
	area_ = area;
}

Area* Object::getArea() {
	return area_;
}

const Model* Object::getModel() {
	return model_;
}
