#include "Camera.hpp"

#include <math.h>
#include <GL/glu.h>
#include <stdlib.h>

#include "console.h"

/**
 * Constructor.
 * @param tag
 */
Camera::Camera(string tag) {
	setTag(tag);
	
	target_ = NULL;

	zoom_.setValue(2.5f);
	zoom_.setThreshold(ZOOM_THRESHOLD);
	zoom_.setRate(ZOOM_SPEED);

	setRotX(-90.0f);
	setRotY(45.0f);

	fov_.setValue(45.0f);
}

#warning ['TODO']: Use this or kill it...
Camera::~Camera() {
}

/**
 * Sets the Object that the camera tracks.
 */
void Camera::setTarget(Object& object) {
	target_ = &object;
}

/**
 * updates the camera's position around object
 */
void Camera::update(const int time) {
	/* http://en.wikipedia.org/wiki/Spherical_coordinates */
	GLfloat theta = getRotX();
	GLfloat phi = getRotY();

	zoom_.update(time);
	fov_.update(time);

	setX(zoom_.getValueCurrent() *
		(cos(theta*(PI/180))) *
		(sin(phi*(PI/180)))
		);

	setY(zoom_.getValueCurrent() *
		(cos(phi*(PI/180)))
		);

	setZ(zoom_.getValueCurrent() *
		(sin(theta*(PI/180))) *
		(sin(phi*(PI/180)))
		);

	Object::update(time);
}

/**
 * Positions the camera for OpenGL.
 */
void Camera::Position() {
	float cx = 0.0f;
	float cy = 0.0f;
	float cz = 0.0f;
	
	if(target_) {
		cx = target_->getX();
		cy = target_->getY();
		cz = target_->getZ();
	}
	
	gluLookAt( getX()+cx, getY()+cy, getZ()+cz, cx, cy, cz, 0.0f, 10.0f, 0.0f );
}

/**
 * Gets the current zoom value
 * @return The zoom value as it actually is, not target value the camera is moving to.
 */
GLfloat Camera::getZoom() {
	return zoom_.getValueCurrent();
}

/**
 * @return The zoom value that the camera it moving to.
 */
GLfloat Camera::getZoomTarget() {
	return zoom_.getValueTarget();
}

/**
 * Gets the current field of view.
 * @return The current FOV (not the target FOV).
 */
GLfloat Camera::getFov() {
	return fov_.getValueCurrent();
}

/**
 * Sets the target field of view.
 * @param fov field of view
 */
void Camera::setFov(const float fov) {
	fov_.setValue(fov);
}

/**
 * Sets the camera zoom (distance from target Object)
 * @param zoom Distance from the target in meters.
 */
void Camera::setZoom(const GLfloat zoom) {
	/* Ensure the camera zoom is sane */
	if(zoom < ZOOM_MIN) {
		zoom_.setValue(ZOOM_MIN);
	} else if(zoom > ZOOM_MAX) {
		zoom_.setValue(ZOOM_MAX);
	} else {
		zoom_.setValue(zoom);
	}
}

/**
 * Sets the camera rotation around the target.
 * @param rx
 */
void Camera::setRotX(const GLfloat rx) {
	Object::setRotX(rx);
}

/**
 * Sets the camera rotation above the target.
 * @param ry
 */
void Camera::setRotY(const GLfloat ry) {
	/* Stop flipping over the top  */
	if(ry < Y_MIN) {
		Object::setRotY(Y_MIN);
	} else if(ry > Y_MAX) {
		Object::setRotY(Y_MAX);
	} else {
		Object::setRotY(ry);
	}
}
