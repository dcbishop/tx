#ifndef TX_PHYSICS_HPP
#define TX_PHYSICS_HPP

#include <btBulletDynamicsCommon.h>

class Physics {
	public:
		Physics();
		~Physics();
	private:
		btAxisSweep3* broadphase_;
		btDefaultCollisionConfiguration* collisionConfiguration_;
		btCollisionDispatcher* dispatcher_;
		btSequentialImpulseConstraintSolver* solver_;
		btDiscreteDynamicsWorld* dynamicsWorld_;
};

#endif
