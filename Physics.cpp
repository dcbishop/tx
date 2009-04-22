#include "Physics.hpp"

Physics::Physics() {
	body_max_ = 16384; /* Maximum number of rigid bodies */

#warning ['TODO']: This should be the size of the world (doesn't seem to effect anything).
	btVector3 worldAabbMin(-10000,-10000,-10000);
	btVector3 worldAabbMax(10000,10000,10000);
	
	broadphase_ = new btAxisSweep3(worldAabbMin,worldAabbMax,body_max_);
	collisionConfiguration_ = new btDefaultCollisionConfiguration();
    dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);
	solver_ = new btSequentialImpulseConstraintSolver;
	
	dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher_,
					broadphase_, solver_, collisionConfiguration_);
	setGravity(GRAVITY_EARTH);
	
	/*BulletDebugdraw *debugdraw = new BulletDebugdraw;
	debugdraw->setDebugMode(1);
	dynamicsWorld_->setDebugdrawer(new BulletDebugdraw);*/
	body_count_ = 0;
}

Physics::~Physics() {
	delete dynamicsWorld_;
    delete solver_;
    delete dispatcher_;
    delete collisionConfiguration_;
    delete broadphase_;
}

/**
 * Returns the bullet broadphase.
 * @see getWorld()
 * @return The broadphase.
 */
btAxisSweep3* Physics::getBroadphase() {
	return broadphase_;
}

/**
 * Returns the physics world.
 * @returns The bullet physics world.
 */
btDiscreteDynamicsWorld* Physics::getWorld() {
	return dynamicsWorld_;
}

/**
 * Sets the gravity used in the physics world.
 * @param gravity
 */
void Physics::setGravity(const float gravity) {
	dynamicsWorld_->setGravity(btVector3(0, -gravity, 0));
}

/**
 * Adds a bullet btRigitBody (NOT the game object RigidBody).
 * @param body The bullet rigid body.
 */
void Physics::addRigidBody(btRigidBody* body) {
	if(body_count_ >= body_max_) {
		return;
	}
	
	body_count_++;
	dynamicsWorld_->addRigidBody(body);
}

/**
 * Removes a bullet btRigidBody from the physics world.
 * @param body The body to remove.
 */
void Physics::removeRigidBody(btRigidBody* body) {
	dynamicsWorld_->removeRigidBody(body);
}

/**
 * updates the physics based on the time.
 * @param time The current game time in milliseconds.
 */
void Physics::update(const int time) {
	#warning ['TODO']: This should be calculated...
	int time_diff = time - getLastupdate();
	if(time_diff <= 0) {
		return;
	}
	btScalar timeStep = ((float)time_diff) / 1000.0f;
	//btScalar timeStep = 1.0f/60.0f;
	//int numsimsteps = dynamicsWorld_->stepSimulation(timeStep,10,1/60.0f);
	int numsimsteps = dynamicsWorld_->stepSimulation(timeStep,0,1.0/60.0);
	//DEBUG_A("dt: %d, Sim steps: %d", time_diff, numsimsteps);
	Updateable::update(time);
}
