#include "RigidBody.hpp"
#include "console.h"

RigidBody::RigidBody() {
	shape_ = NULL;
	body_ = NULL;
	mass_ = 1;
	
	motionState_ = new btDefaultMotionState(
					btTransform(btQuaternion(0,0,0,1),
					btVector3(0,0,0))
	);

}

void RigidBody::setShape(btCollisionShape* shape) {
	if(body_) {
		#warning ['TODO']: If there is already a body... need to update it somehow?
		//body_
	} else {
		#warning ['TODO']: Otherwise make a new body...
	}
	
	if(shape_) {
		delete shape_;
	}
	
	shape_ = shape;
	shape_->calculateLocalInertia(mass_, inertia_);
	
	if(!body_) {
		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
			mass_,
			motionState_,
			shape_,
			inertia_
		);
		body_ = new btRigidBody(rigidBodyCI);
	}	
}

void RigidBody::setArea(Area* area) {
	Area* old_area = getArea();
	if(old_area) { /* If its already in an area */
		#warning ['TODO']: Check to see if both areas are using the same physics engine...
			#warning ['TODO']: If not remove shape from old area physics...
	}
	
	Object::setArea(area);
	
	if(body_) {
		#warning ['TODO']: Add body to physics, but only if it isn't already in an engine...
		if(getArea() && getArea()->getPhysics()) {
			getArea()->getPhysics()->addRigidBody(body_);
		}
	}
}

void RigidBody::removeRigidBody_() {
	Area* area = getArea();
	if(area && area->getPhysics() && body_) {
		area->getPhysics()->removeRigidBody(body_);
	}
}

RigidBody::~RigidBody() {
	removeRigidBody_();
	
	delete body_;
	delete shape_;
	delete motionState_;
}

#warning ['TODO']: Implement getPos, setPos&XYZ
const float RigidBody::getX() {
	if(!body_) {
		return 0.0f;
	}
	
	btTransform trans;
    body_->getMotionState()->getWorldTransform(trans);
	return trans.getOrigin().getX();
}

const float RigidBody::getY() {
	if(!body_) {
		return 0.0f;
	}
	
	btTransform trans;
    body_->getMotionState()->getWorldTransform(trans);
	return trans.getOrigin().getY();
}

const float RigidBody::getZ() {
	if(!body_) {
		return 0.0f;
	}
	
	btTransform trans;
    body_->getMotionState()->getWorldTransform(trans);
	return trans.getOrigin().getZ();
}

void RigidBody::Update(int time) {
	Area* area = getArea();
	if(!area || area->getPhysics()) {
		area->getPhysics()->Update(time);
	}
}

void RigidBody::setMass(btScalar mass) {
	mass_ = mass;
}

void RigidBody::setPos(float x, float y, float z) {
	if(body_) {
		body_->getWorldTransform().setOrigin( btVector3(x, y, z) );
	}
}

void RigidBody::setX(float x) {
	if(body_) {
		body_->getWorldTransform().setOrigin( btVector3(x, getY(), getZ()) );
	}
}

void RigidBody::setY(float y) {
	if(body_) {
		body_->getWorldTransform().setOrigin( btVector3(getX(), y, getZ()) );
	}
}

void RigidBody::setZ(float z) {
	if(body_) {
		body_->getWorldTransform().setOrigin( btVector3(getX(), getY(), z) );
	}
}

void drawCube() {
	float z;
	float BOX_SIZE = 0.5f;
	glColor3f(1.0f, 0.0f, 0.0f);

	/* Draw Cube */
	glBegin(GL_LINES);
		/* Draw front and back of cube */
		for(z = -BOX_SIZE; z<=BOX_SIZE; z++) {
			glVertex3f(-BOX_SIZE, BOX_SIZE, z);
			glVertex3f(BOX_SIZE, BOX_SIZE, z);

			glVertex3f(BOX_SIZE, BOX_SIZE, z);
			glVertex3f(BOX_SIZE, -BOX_SIZE, z);

			glVertex3f(BOX_SIZE, -BOX_SIZE, z);
			glVertex3f(-BOX_SIZE, -BOX_SIZE, z);

			glVertex3f(-BOX_SIZE, -BOX_SIZE, z);
			glVertex3f(-BOX_SIZE, BOX_SIZE, z);
		}

		/* Draw sides lines */
		glVertex3f(BOX_SIZE, BOX_SIZE, BOX_SIZE);
		glVertex3f(BOX_SIZE, BOX_SIZE, -BOX_SIZE);

		glVertex3f(-BOX_SIZE, BOX_SIZE, BOX_SIZE);
		glVertex3f(-BOX_SIZE, BOX_SIZE, -BOX_SIZE);

		glVertex3f(BOX_SIZE, -BOX_SIZE, BOX_SIZE);
		glVertex3f(BOX_SIZE, -BOX_SIZE, -BOX_SIZE);

		glVertex3f(-BOX_SIZE, -BOX_SIZE, BOX_SIZE);
		glVertex3f(-BOX_SIZE, -BOX_SIZE, -BOX_SIZE);
	glEnd();
}

void RigidBody::Draw() {
	const Model* model = getModel();
	if(!model || !body_) {
		return;
	}
	
	glPushMatrix();
	btScalar m[15];
	body_->getWorldTransform().getOpenGLMatrix(m);
	glMultMatrixf(m);
	drawCube();
	
	RCBC_Render(model);
	glPopMatrix();
}
