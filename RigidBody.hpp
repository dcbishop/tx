#ifndef TX_RIGIDBODY_HPP
#define TX_RIGIDBODY_HPP

#include "Object.hpp"
#include "Physics.hpp"

/**
 * A dynamic rigid body object.
 */
class RigidBody : public Object {
	public:
		RigidBody(string tag = DEFAULT_TAG);
		~RigidBody();
		virtual void setArea(Area* area);
		virtual void setShape(btCollisionShape* shape);
		virtual btVector3& getPos();
		virtual const float getX();
		virtual const float getY();
		virtual const float getZ();
		virtual void Update(const int time);
		virtual void setMass(const btScalar mass);
		virtual void setPos(const float x, const float y, const float z);
		virtual void setX(const float x);
		virtual void setY(const float y);
		virtual void setZ(const float z);
		virtual void Draw();
		virtual btRigidBody* getBody();
	
	protected:
		btCollisionShape* shape_; /**< The collision shape. */
		btCollisionObject* body_; /**< The collision body. */
		
	private:
		void removeRigidBody_();
		btDefaultMotionState* motionState_;
		btScalar mass_;
		btVector3 inertia_;
	
};

#endif
