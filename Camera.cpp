#include "Camera.hpp"

#include <math.h>
#include <GL/glu.h>
#include <stdlib.h>

#include "console.h"

Camera::Camera() {
	target_ = NULL;

	zoom_.setValue(2.5f);
	zoom_.setThreshold(ZOOM_THRESHOLD);
	zoom_.setRate(ZOOM_SPEED);

	setRotX(-90.0f);
	setRotY(45.0f);

	fov_.setValue(45.0f);
}

#warning ['TODO']: Use this of kill it...
Camera::~Camera() {
}

void Camera::setTarget(Object* object) {
	target_ = object;
}

void Camera::Draw() {
}

/* Position camera around object using some voodoo math */
void Camera::Update(int time) {
	/* http://en.wikipedia.org/wiki/Spherical_coordinates */
	GLfloat theta = getRotX();
	GLfloat phi = getRotY();

	zoom_.Update(time);
	fov_.Update(time);

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

	Object::Update(time);
}

void Camera::Position() {
	float cx = 0.0f;
	float cy = 0.0f;
	float cz = 0.0f;
	
	if(target_) {
		cx = target_->getX();
		cy = target_->getY();
		cz = target_->getZ();
	}
	
	gluLookAt( getX()-cx, getY()+cy, getZ()-cz, -cx, cy, -cz, 0.0f, 10.0f, 0.0f );
}

GLfloat Camera::getZoom() {
	return zoom_.getValueCurrent();
}

GLfloat Camera::getZoomTarget() {
	return zoom_.getValueTarget();
}

GLfloat Camera::getFov() {
	return fov_.getValueCurrent();
}

void Camera::setFov(float fov) {
	fov_.setValue(fov);
}

void Camera::setZoom(GLfloat zoom) {
	/* Ensure the camera zoom is sane */
	if(zoom < ZOOM_MIN) {
		zoom = ZOOM_MIN;
	} else if(zoom > ZOOM_MAX) {
		zoom = ZOOM_MAX;
	}

	zoom_.setValue(zoom);
}

void Camera::setRotX(const GLfloat rx) {
	Object::setRotX(rx);
}

void Camera::setRotY(GLfloat ry) {
	/* Stop flipping over the top  */
	if(ry < Y_MIN) {
		ry = Y_MIN;
	} else if(ry > Y_MAX) {
		ry = Y_MAX;
	}

	Object::setRotY(ry);
}
