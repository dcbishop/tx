#include "RigidBody.hpp"
#include "console.h"

/**
 * Constructor
 * @param tag
 */
RigidBody::RigidBody(const string tag) {
	setTag(tag);
	
	shape_ = NULL;
	body_ = NULL;
	mass_ = 1.0f;
	
	motionState_ = new btDefaultMotionState(
					btTransform(btQuaternion(0,0,0,1),
					btVector3(0,0,0))
	);
}

RigidBody::~RigidBody() {
	removeRigidBody_();
	
	delete body_;
	delete shape_;
	delete motionState_;
}

/**
 * Sets the bullet collision shape.
 * @param shape The collision shape.
 */
void RigidBody::setShape(btCollisionShape* shape) {
	if(body_) {
		#warning ['TODO']: If there is already a body... need to update it somehow?
	} else {
		#warning ['TODO']: Otherwise make a new body...
	}
	
	if(shape_ && shape != shape_) {
		delete shape_;
	}
	
	shape_ = shape;
	shape_->calculateLocalInertia(mass_, inertia_);
	delete(body_);
	
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
		mass_,
		motionState_,
		shape_,
		inertia_
	);
	
	body_ = new btRigidBody(rigidBodyCI);
}

void RigidBody::setArea(Area& area) {
	Area* old_area = getArea();
	if(old_area) { /* If its already in an area */
		#warning ['TODO']: Check to see if both areas are using the same physics engine...
			#warning ['TODO']: If not remove shape from old area physics...
	}
	
	Object::setArea(area);
	
	if(body_) {
		#warning ['TODO']: Add body to physics, but only if it isn't already in an engine...
		if(getArea() && getArea()->getPhysics()) {
			getArea()->getPhysics()->addRigidBody((btRigidBody*)body_);
		}
	}
}

void RigidBody::removeRigidBody_() {
	Area* area = getArea();
	if(area && area->getPhysics() && body_) {
		area->getPhysics()->removeRigidBody((btRigidBody*)body_);
	}
}

#warning ['TODO']: Might be best as a generic struct of float and in Object class
/**
 * @return a vector containing the x, y, z cordinates.
 */
btVector3& RigidBody::getPos() {
	if(!body_) {
		throw "No body...";
	}
	btTransform trans = body_->getWorldTransform();
	return trans.getOrigin();
}

const float RigidBody::getX() {
	try {
		return getPos().getX();
	} catch(char const* str) {
		return Object::getX();
	}
}

const float RigidBody::getY() {
	try {
		return getPos().getY();
	} catch(char const* str) {
		return Object::getY();
	}
}

const float RigidBody::getZ() {
	try {
		return getPos().getZ();
	} catch(char const* str) {
		return Object::getZ();
	}
}

void RigidBody::Update(int time) {
	Object::Update(time);
}

/**
 * Sets the mass of the Object.
 * @param mass
 */
void RigidBody::setMass(const btScalar mass) {
	mass_ = mass;
}

void RigidBody::setPos(const float x, const float y, const float z) {
	if(body_) {
		body_->getWorldTransform().setOrigin( btVector3(x, y, z) );
	}
}

void RigidBody::setX(const float x) {
	if(body_) {
		body_->getWorldTransform().setOrigin( btVector3(x, getY(), getZ()) );
	}
}

void RigidBody::setY(const float y) {
	if(body_) {
		body_->getWorldTransform().setOrigin( btVector3(getX(), y, getZ()) );
	}
}

void RigidBody::setZ(const float z) {
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
	const Model* model = &getModel();
	if(!model || !body_) {
		return;
	}
	
	glPushMatrix();
	btScalar m[15];
	body_->getWorldTransform().getOpenGLMatrix(m);
	m[12] = -m[12]; // Need to reverse this to rotate correctly o_O.
	glMultMatrixf(m);
	glDisable(GL_LIGHTING);
	drawCube();
	glEnable(GL_LIGHTING);
	RCBC_Render(model);
	glPopMatrix();
}

/**
 * Returns the Object's physics body.
 */
btRigidBody& RigidBody::getBody() {
	return (btRigidBody&)(*body_);
}
