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
	DEBUG_M("Entering function...");
	setArea(NULL);
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
	rb->processBody_();
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

	Area* area = getArea();
	Physics* physics = NULL;
	if(area) {
		physics = getArea()->getPhysics();
	}
	removeBody(physics);

	if(shape_ && shape != shape_) {
		//delete shape_;
	}

	shape_ = shape;
	processBody_();
}

/**
 * Processes the properties of the body, shape, mass friction, etc...
 */
void RigidBody::processBody_() {

	// Remove the current body from the physics engine
	Area* area = getArea();
	Physics* physics = NULL;
	if(area) {
		physics = getArea()->getPhysics();
	}
	removeBody(physics);

	if(!shape_) {
		return;
	}

	shape_->calculateLocalInertia(mass_, inertia_);

	float x = getX();
	float y = getY();
	float z = getZ();
	
	if(body_) {
		delete(body_);
	}// else {

		//btTransform xform;
		//xform = motionState_.getWorldTransform();
		//xform.setRotation(btQuaternion (btVector3(getRotX(), getRotY(), getRotZ()), getRotAngle()*(PI/180)));
		//xform.setOrigin(
		//((btPairCachingGhostObject*)body_)->setWorldTransform (xform);
		//motionState_->setWorldTransform (xform);
		
		/*btTransform xform;
		motionState_->getWorldTransform(xform);
		xform.setOrigin(btVector3(getX(), getY(), getZ()));
		motionState_->setWorldTransform(xform);*/
	//}

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
		mass_,
		motionState_,
		shape_,
		inertia_
	);
	rigidBodyCI.m_friction = friction_;
	rigidBodyCI.m_mass = mass_;

	body_ = new btRigidBody(rigidBodyCI);
	setXYZ(x, y, z);
	addBody(physics);

	/*btRigidBody* rb = dynamic_cast<btRigidBody*>(body_);
	if(rb) {
		rb->clearForces();
	}*/
}

/**
 * Adds a physic body to the physics engine.
 * @param physics The physics engine to add to.
 */
void RigidBody::addBody(Physics* physics) {
	DEBUG_M("Entering function...");
	if(!physics) {
		return;
	}
	if(body_) {
		physics->addRigidBody((btRigidBody*)body_);
		//physics->addCollisionObject(body_);
	}
}

/**
 * Remove a physic body to the physics engine.
 * @param physics The physics engine to remove from.
 */
void RigidBody::removeBody(Physics* physics) {
	DEBUG_M("Entering function...");
	if(!physics) {
		return;
	}
	if(body_) {
		physics->removeRigidBody((btRigidBody*)body_);
	}
}

#warning ['TODO']: Might be best as a generic struct of float and in Object class
/**
 * @return a vector containing the -x, y, z coordinates.
 */
btVector3& RigidBody::getPos() {
	if(!body_) {
		//DEBUG_A("RigidBody: '%s' has no body", getTag().c_str());
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
	// this function is different, getX,getY style was causing 
	// uniniitilized data to be returned but only sometimes.
	float z = 0.0f;
	//try {
		if(body_) {
			btTransform &transform = body_->getWorldTransform();
			z = transform.getOrigin().getZ();
			//z = getPos().getZ();
		} else {
	//} catch(char const* str) {
		//DEBUG_A("GetZ error");
		z = Object::getZ();
	}
	//DEBUG_A("GetZ %f", z);
	return z;
}

/**
 * Sets the mass of the body.
 * @param mass
 */
void RigidBody::setMass(const btScalar mass) {
	mass_ = mass;
	processBody_();
}

/**
 * Sets the friction of the body.
 * @param friction The friction.
 */
void RigidBody::setFriction(const btScalar friction) {
	friction_ = friction;
	processBody_();
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
	if(!&model) {
		return;
	}

	if(!body_) {
		Object::draw(interface);
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

	preDraw(interface);
	model.draw(interface);
	postDraw(interface);

	glPopMatrix();
}

/**
 * Returns the Object's physics body.
 */
btRigidBody& RigidBody::getBody() {
	return (btRigidBody&)(*body_);
}

#warning ['TODO']: This function doesnt work correctly, it ignores the models scale, rotation information and seems to have problems actually colliding falling through the ground
void RigidBody::loadShapeFromModel_ProcessNode_(SceneNode* node, btCompoundShape* combined) {
	DEBUG_M("Entering function...");
	Mesh* mesh = node->mesh;
	if(!mesh) {
		return;
	}

	Triangles* triangles = mesh->triangles;
	if(!triangles) {
		return;
	}

	FloatArray* vertices = triangles->vertices;
	if(!vertices) {
		return;
	}

	/*btBvhTriangleMeshShape* meshShape
	btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray();*/
	/*btTriangleMesh* triangleMesh = new btTriangleMesh();
	for(int i = 0; i < vertices->count; i+=3) {
		btVector3* vertex = new btVector3(vertices->values[i], vertices->values[i+1], vertices->values[i+2]);
		triangleMesh->addTriangle(vertex, true);
	}*/
	DEBUG_H("\tFlag...");
	// We need to make a fake index since the vertex data isn't indexed but its required by bullet
	int* triangleIndexBase = (int*)malloc(vertices->count * sizeof(int));
	for(int i = 0; i < vertices->count; i++) {
		triangleIndexBase[i] = i;
	}
	DEBUG_H("\tFlag...");
	int numTriangles = vertices->count / 3;
	int triangleIndexStride = sizeof(int) * 3;
	int vertexStride = sizeof(float) * 3;

	DEBUG_H("\tFlag...");
	btTriangleIndexVertexArray* triArray = new btTriangleIndexVertexArray(
		numTriangles,
		triangleIndexBase,
		triangleIndexStride,
		vertices->count,
		vertices->values,
		vertexStride
	);

	DEBUG_H("\tFlag...");
	// Turn triangles into a mesh...
	// Offset the mesh position...
	// Add mesh to combined object...
	float x = node->translate[0];
	float y = node->translate[1];
	float z = node->translate[2];

	DEBUG_H("\tFlag...");
	//float rx = mesh->rotations
	btQuaternion rot(0, 1, 0, 0);
	ListNode* rot_node = node->rotations->first;
	while(rot_node) {
		DEBUG_H("\t\tlooping node...");
		Rotate* rotate = (Rotate*)rot_node->data;
		if(rotate) {
			DEBUG_H("\t\t\trotate...");
			float rx = rotate->x;
			float ry = rotate->y;
			float rz = rotate->z;
			float ra = rotate->angle;
			//btQuaternion addRotation(btVector3(rx, ry, rz), ra);
			//rotation = rotation + addRotation;
			//rotation += addRotation;//btQuaternion(btVector3(rx, ry, rz), ra);
			//rotation.operator+=(addRotation);
			rot += btQuaternion(btVector3(rx, ry, rz), ra);
		}
		DEBUG_H("\tnext...");
		rot_node = rot_node->next;
	}

	DEBUG_H("\tmake mesh...");
	//btTransform* transform = new btTransform(rot, btVector3(x, y, z));
	btBvhTriangleMeshShape* trimeshShape = new btBvhTriangleMeshShape(triArray, true);
	DEBUG_H("\ttest...");
	combined->addChildShape(btTransform(rot, btVector3(x, y, z)), trimeshShape);
	//free(indices);
	#warning ['TODO']: Free indices
	DEBUG_H("\texiting function...");
}


btCollisionShape* RigidBody::loadShapeFromModel_ProcessNodes_(SceneNode* node, btCompoundShape* shape) {
	DEBUG_M("Entering function...");
	while(node) {
		loadShapeFromModel_ProcessNode_(node, shape);
		if(node->child) {
			loadShapeFromModel_ProcessNodes_(node->child, shape);
		}
		node = node->next;
	}
	return shape;
}

btCollisionShape* RigidBody::loadShapeFromModel(RigidBody* body) {//Visual* visual) {
	DEBUG_M("Entering function...");
	#warning ['TODO']: Store shapes like models...
	Visual& visual = body->getVisual();
	/*if(!visual) {
		return NULL;
	}*/
	btCompoundShape* shape = new btCompoundShape();
	/*Visual& visual = getVisual();*/
	VModel* vmodel = dynamic_cast<VModel*>(&visual);
	if(!vmodel) {
		//return NULL;
		return NULL;
	}

	ResourceManager temprm;
	Model* model = temprm.loadModel(vmodel->getFilename());
	if(!model) {
		return NULL;
	}

	SceneNode* sn = model->visual_scene;
	if(!sn) {
		return NULL;
	}

	return loadShapeFromModel_ProcessNodes_(sn, shape);

	/*Model* model = rm->loadModel(vmodel.getFilename()) ;
	
	btTriangleIndexVertexArray* indexVertexArrays = new
		btTriangleIndexVertexArray(model->count*/
}

/**
 * Loads a bullet box collision shape.
 * @param x x size.
 * @param y y size.
 * @param z z size.
 */
btCollisionShape* RigidBody::loadShapeBox(const float x, const float y, const float z) {
	return new btBoxShape(btVector3(x , y, z));
}

/**
 * Stops the RigidBody from being able to be rotated.
 */
void RigidBody::disableRotation() {
	btRigidBody* rb = dynamic_cast<btRigidBody*>(body_);
	if(rb) {
		rb->setAngularFactor(0.0);
	}
}

void RigidBody::setKinematic() {
	setMass(0.0);
	body_->setCollisionFlags( body_->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	body_->setActivationState(DISABLE_DEACTIVATION);
}

void RigidBody::stopMovement() {
	
}

#warning ['TODO']: Provide rotation accessors...
