#include "Physics.hpp"

Physics::Physics() {
	body_max_ = 1024; /* Maximum number of rigid bodies */

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
	
	last_update_ = 0;
	BulletDebugDraw *debugdraw = new BulletDebugDraw;
	debugdraw->setDebugMode(1);
	dynamicsWorld_->setDebugDrawer(new BulletDebugDraw);
	body_count_ = 0;
}

Physics::~Physics() {
	delete dynamicsWorld_;
    delete solver_;
    delete dispatcher_;
    delete collisionConfiguration_;
    delete broadphase_;
}

btAxisSweep3* Physics::getBroadphase() {
	return broadphase_;
}

btDiscreteDynamicsWorld* Physics::getWorld() {
	return dynamicsWorld_;
}

void Physics::setGravity(float gravity) {
	dynamicsWorld_->setGravity(btVector3(0, -gravity, 0));
}

void Physics::addRigidBody(btRigidBody* body) {
	if(body_count_ >= body_max_) {
		return;
	}
	
	body_count_++;
	dynamicsWorld_->addRigidBody(body);
}

void Physics::removeRigidBody(btRigidBody* body) {
	dynamicsWorld_->removeRigidBody(body);
}

void Physics::Update(int time) {
	#warning ['TODO']: This should be calculated...
	int time_diff = time - last_update_;
	
	btScalar timeStep = ((float)time_diff) / 1000.0f;
	int numsimsteps = dynamicsWorld_->stepSimulation(timeStep,1);
	last_update_ = time;
}

void Physics::debugDrawWorld(){
	dynamicsWorld_->debugDrawWorld();
}
