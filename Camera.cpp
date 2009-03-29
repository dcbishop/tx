#include "Camera.hpp"

#include <math.h>
#include <GL/glu.h>
#include <stdlib.h>

#include "console.h"

Camera::Camera() {
	target_ = NULL;
	
	zoom_ = 2.5f;
	setRotX(-90.0f);
	setRotY(45.0f);
	
	fov_ = 90.0f;
}

Camera::~Camera() {
}

void Camera::setTarget(const Object* object) {
	target_ = object;
}

void Camera::Draw() {
}

/* Position camera around object using some voodoo math */
void Camera::Update(int time) {
	/* http://en.wikipedia.org/wiki/Spherical_coordinates */
	GLfloat theta = getRotX();
	GLfloat phi = getRotY();

	setX(getZoom() * (cos(theta*(PI/180))) * (sin(phi*(PI/180))));
	setY(getZoom() * (cos(phi*(PI/180))));
	setZ(getZoom() * (sin(theta*(PI/180))) * (sin(phi*(PI/180))));
	Object::Update(time);
}

void Camera::Position() {
	gluLookAt( getX(), getY(), getZ(), 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f );
}

GLfloat Camera::getZoom() {
	return zoom_;
}

GLfloat Camera::getFov() {
	return fov_;
}


void Camera::setZoom(const GLfloat zoom) {
	zoom_ = zoom;
	
	/* Ensure the camera zoom is sane */
	if(zoom_ < ZOOM_MIN) {
		zoom_ = ZOOM_MIN;
	} else if(zoom_ > ZOOM_MAX) {
		zoom_ = ZOOM_MAX;
	}
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
