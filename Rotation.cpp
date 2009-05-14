#include "Rotation.hpp"

//#include <stdlib.h>
#include <math.h> // For fmodf

Rotation& Rotation::getRotation() {
	return *this;
}

void Rotation::setRotation(Rotation& rotation) {
	setRotX(rotation.getRotX());
	setRotY(rotation.getRotY());
	setRotZ(rotation.getRotZ());
	setRotAngle(rotation.getRotAngle());
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
 * @param rx the X rotation in OpenGL coordinates.
 */
void Rotation::setRotX(const float rx) {
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
 * @param ry the Y rotation in OpenGL coordinates.
 */
void Rotation::setRotY(const float ry) {
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
 * @param rz the Z rotation in OpenGL coordinates.
 */
void Rotation::setRotZ(const float rz) {
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
 * @param angle the angle of rotation in OpenGL coordinates.
 */
void Rotation::setRotAngle(const float angle) {
	angle_ = angle;
	setRot_();
}

/**
 * For fixing any changes to the rotation data.
 */
void Rotation::setRot_() {
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
 * @return the X rotation in OpenGL coordinates.
 */
const float Rotation::getRotX() {
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
 * @return the Y rotation in OpenGL coordinates.
 */
const float Rotation::getRotY() {
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
 * @return the Z rotation in OpenGL coordinates.
 */
const float Rotation::getRotZ() {
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
 * @return the angle of rotation in OpenGL coordinates.
 */
const float Rotation::getRotAngle() {
	return angle_;
}
