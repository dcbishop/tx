#include "RigidBody.hpp"

#include "Area.hpp"
#include "Interface.hpp"

#include "console.h"


/**
 * Constructor.
 * @param tag
 * @param model
 */
RigidBody::RigidBody(const string tag, Visual* model) {
	setTag(tag);

	setVisual(model);
	shape_ = NULL;
	body_ = NULL;
	mass_ = 1.0f;
	friction_ = 1.0f;

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
 * Copy constructor.
 * @return A deep copy of this object.
 */
Object* RigidBody::clone() {
	RigidBody* rb = new RigidBody(*this);
	//rb.setShape(new rb
	rb->body_ = NULL;
	rb->ProcessBody_();
	return rb;
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
	ProcessBody_();
}

/**
 * Processes the properties of the body, shape, mass friction, etc...
 */
void RigidBody::ProcessBody_() {
	if(!shape_) {
		return;
	}
	
	shape_->calculateLocalInertia(mass_, inertia_);
	delete(body_);
	
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
		mass_,
		motionState_,
		shape_,
		inertia_
	);
	rigidBodyCI.m_friction = friction_;
	rigidBodyCI.m_mass = mass_;
	
	body_ = new btRigidBody(rigidBodyCI);
}

void RigidBody::setArea(Area& area) {
	Area* old_area = getArea();
	if(old_area) { // If its already in an area
		#warning ['TODO']: Check to see if both areas are using the same physics engine...
			#warning ['TODO']: If not remove shape from old area physics...
	}
	
	Object::setArea(area);
	
	if(body_) {
		#warning ['TODO']: Add body to physics, but only if it isnt already in an engine...
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
 * @return a vector containing the -x, y, z coordinates.
 */
btVector3& RigidBody::getPos() {
	if(!body_) {
		DEBUG_A("RigidBody: '%s' has no body", getTag().c_str());
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

/**
 * Sets the mass of the body.
 * @param mass
 */
void RigidBody::setMass(const btScalar mass) {
	mass_ = mass;
	ProcessBody_();
}

/**
 * Sets the friction of the body.
 * @param friction The friction.
 */
void RigidBody::setFriction(const btScalar friction) {
	friction_ = friction;
	ProcessBody_();
}

void RigidBody::setXYZ(const float x, const float y, const float z) {
	if(body_) {
		body_->getWorldTransform().setOrigin( btVector3(x, y, z) );
	}
	Object::setXYZ(x, y, z);
}

void RigidBody::setX(const float x) {
	setXYZ(x, getY(), getZ());
}

void RigidBody::setY(const float y) {
	setXYZ(getX(), y, getZ());
}

void RigidBody::setZ(const float z) {
	setXYZ(getX(), getY(), z);
}

void RigidBody::setRot_() {
	if(!body_) {
		return;
	}

	btTransform xform;
	xform = getBody().getWorldTransform();
	xform.setRotation(btQuaternion (btVector3(getRotX(), getRotY(), getRotZ()), getRotAngle()*(PI/180)));
	//((btPairCachingGhostObject*)body_)->setWorldTransform (xform);
	body_->setWorldTransform (xform);
}

void RigidBody::setRotX(const float x) {
	Object::setRotX(x);
	setRot_();
}

void RigidBody::setRotY(const float y) {
	Object::setRotY(y);
	setRot_();
}

void RigidBody::setRotZ(const float z) {
	Object::setRotZ(z);
	setRot_();
}

void RigidBody::setRotAngle(const float angle) {
	Object::setRotAngle(angle);
	setRot_();
}

void drawCube() {
	float z;
	float BOX_SIZE = 0.5f;
	glColor3f(1.0f, 0.0f, 0.0f);

	// draw Cube
	glBegin(GL_LINES);
		// draw front and back of cube
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

		// draw sides lines
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

void RigidBody::draw(Interface* interface) {
	ResourceManager* rm = interface->getResourceManager();
	if(!rm || !isVisible()) {
		return;
	}

	Visual& model = getVisual();
	if(!&model || !body_) {
		return;
	}

	glPushMatrix();

	btScalar m[16];
	btTransform &transform = body_->getWorldTransform();
	transform.getOpenGLMatrix(m);

	glMultMatrixf(m);

	/*glDisable(GL_LIGHTING);
	drawCube();
	glEnable(GL_LIGHTING);*/
	model.draw(interface);

	glPopMatrix();
}

/**
 * Returns the Object's physics body.
 */
btRigidBody& RigidBody::getBody() {
	return (btRigidBody&)(*body_);
}

#warning ['TODO']: Provide rotation accessors...
