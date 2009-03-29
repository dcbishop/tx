#include "Object.hpp"

#include <GL/gl.h>

#include "console.h"

Object::Object() {
	model_ = NULL;
	setX(0.0f);
	setY(0.0f);
	setZ(0.0f);
	setRotX(0.0f);
	setRotY(0.0f);
	setRotZ(0.0f);
	setRotX(-90.0f);

#warning ['TODO']: This shoud be the current time...
	last_update_ = 0;
}

Object::~Object() {
}

void Object::Draw() {
	glPushMatrix();
	glTranslatef(getX(), getY(), getZ());
	glRotatef(getAngle(), getRotX(), getRotY(), getRotZ());
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

float Object::getX() {
	return x_;
}

float Object::getY() {
	return y_;
}

float Object::getZ() {
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

float Object::getRotX() {
	return rx_;
}

float Object::getRotY() {
	return ry_;
}

float Object::getRotZ() {
	return rz_;
}

float Object::getAngle() {
	return angle_;
}
