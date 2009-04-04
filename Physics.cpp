#include "Physics.hpp"

Physics::Physics() {
	int maxProxies = 1024; /* Maximum number of rigid bodies */
#warning ['TODO']: This should be the size of the world.
	btVector3 worldAabbMin(-10000,-10000,-10000);
	btVector3 worldAabbMax(10000,10000,10000);
	
	broadphase_ = new btAxisSweep3(worldAabbMin,worldAabbMax,maxProxies);
	collisionConfiguration_ = new btDefaultCollisionConfiguration();
    dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);
	solver_ = new btSequentialImpulseConstraintSolver;
	
	dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher_,
					broadphase_, solver_, collisionConfiguration_);
	
#warning ['TODO']: Isn't this a little bit off? 9.8 or something...
	dynamicsWorld_->setGravity(btVector3(0,-10,0));	
}

Physics::~Physics() {
	delete dynamicsWorld_;
    delete solver_;
    delete dispatcher_;
    delete collisionConfiguration_;
    delete broadphase_;
}
