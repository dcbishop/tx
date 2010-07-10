#ifndef TX_PHYSICS_HPP
#define TX_PHYSICS_HPP

#include <btBulletDynamicsCommon.h>
#include <GL/gl.h>
#include "console.h"

#include "Updateable.hpp"
#include "GLDebugDrawer.h"

const float GRAVITY_MERCURY	=	3.7f;
const float GRAVITY_VENUS	=	8.8f;
const float GRAVITY_EARTH	=	9.8f;
const float GRAVITY_MOON	=	1.6f;
const float GRAVITY_MARS	=	3.7f;
const float GRAVITY_JUPITER	=	23.2f;
const float GRAVITY_SATURN	=	9.0f;
const float GRAVITY_URANUS	=	8.7f;
const float GRAVITY_NEPTUNE	=	11.1f;
const float GRAVITY_PLUTO	=	0.6f;

/**
 * A class responsible for running the games physics.
 */
class Physics : public Updateable {
	public:
		Physics();
		~Physics();
		virtual void update(const int time);
		virtual void addRigidBody(btRigidBody* body);
		virtual void removeRigidBody(btRigidBody* body);
		virtual void setGravity(const float gravity);
		virtual btAxisSweep3* getBroadphase();
		virtual btDiscreteDynamicsWorld* getWorld();

	private:
		btAxisSweep3* broadphase_;
		btDefaultCollisionConfiguration* collisionConfiguration_;
		btCollisionDispatcher* dispatcher_;
		btSequentialImpulseConstraintSolver* solver_;
		btDiscreteDynamicsWorld* dynamicsWorld_;
		int body_count_;
		int body_max_;
		//GLDebugDrawer gDebugDrawer_;
};

#endif /* TX_PHYSICS_HPP */
