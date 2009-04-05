#ifndef TX_RIGIDBODY_HPP
#define TX_RIGIDBODY_HPP

#include "Object.hpp"
#include "Physics.hpp"

class RigidBody : public Object {
	public:
		RigidBody();
		~RigidBody();
		void setArea(Area* area);
		void setShape(btCollisionShape* shape);
		const float getX();
		const float getY();
		const float getZ();
		void Update(int time);
		void setMass(btScalar mass);
		void setPos(float x, float y, float z);
		void setX(float x);
		void setY(float y);
		void setZ(float z);
		void Draw();
		
	private:
		void removeRigidBody_();
		btCollisionShape* shape_;
		btRigidBody* body_;
		btDefaultMotionState* motionState_;
		btScalar mass_;
		btVector3 inertia_;
};

#endif
