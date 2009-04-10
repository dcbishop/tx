#ifndef TX_PHYSICS_HPP
#define TX_PHYSICS_HPP

#include <btBulletDynamicsCommon.h>
#include <GL/gl.h>
#include "console.h"

const float GRAVITY_MERCURY	=	3.7f;
const float GRAVITY_VENUS	=	8.8f;
const float GRAVITY_EARTH	=	9.8f;
const float GRAVITY_MOON	=	1.6f;
const float GRAVITY_MARS	=	3.7f;
const float GRAVITY_JUPITER =	23.2f;
const float GRAVITY_SATURN	=	9.0f;
const float GRAVITY_URANUS	=	8.7f;
const float GRAVITY_NEPTUNE	=	11.1f;
const float GRAVITY_PLUTO	=	0.6f;

class Physics {
	public:
		Physics();
		~Physics();
		virtual void Update(int time);
		virtual void addRigidBody(btRigidBody* body);
		virtual void removeRigidBody(btRigidBody* body);
		virtual void setGravity(float gravity);
		virtual void debugDrawWorld();
		virtual btAxisSweep3* getBroadphase();
		virtual btDiscreteDynamicsWorld* getWorld();


	private:
		btAxisSweep3* broadphase_;
		btDefaultCollisionConfiguration* collisionConfiguration_;
		btCollisionDispatcher* dispatcher_;
		btSequentialImpulseConstraintSolver* solver_;
		btDiscreteDynamicsWorld* dynamicsWorld_;
		int last_update_;
		int body_count_;
		int body_max_;
};

class BulletDebugDraw : public btIDebugDraw {
	public:
		void drawLine(const btVector3& from,const btVector3& to,const btVector3& colour) {
			glBegin(GL_LINES);
				glColor3f(colour.getX(), colour.getY(), colour.getZ());
				glVertex3d(from.getX(), from.getY(), from.getZ());
				glVertex3d(to.getX(), to.getY(), to.getZ());
			glEnd();
		}
		
		void drawContactPoint(const btVector3& pob, const btVector3& nob, btScalar distance, int life, const btVector3& colour) {
		}
		
		void draw3dText(const btVector3& pos, const char* text) {
			DEBUG_A("%s", text);
		}
		
		void setDebugMode(int debug)
		{
			debug_ = debug;
		}
		
		void reportErrorWarning(const char * warningString)
		{
			ERROR("%s", warningString);
		}

		int getDebugMode() const {
			return debug_;
		}
	private:
		int debug_;

};

#endif
