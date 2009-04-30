#ifndef TX_RIGIDBODY_HPP
#define TX_RIGIDBODY_HPP

class Area;
#include "Object.hpp"
#include "Physics.hpp"

/**
 * A dynamic rigid body object.
 */
class RigidBody : public Object {
	public:
		RigidBody(string tag = DEFAULT_TAG, Visual* model = NULL);
		~RigidBody();
		virtual Object* clone();
		virtual void setArea(Area& area);
		virtual void setShape(btCollisionShape* shape);
		virtual btVector3& getPos();
		virtual const float getX();
		virtual const float getY();
		virtual const float getZ();
		virtual void setMass(const btScalar mass);
		virtual void setFriction(const btScalar friction);
		virtual void setPos(const float x, const float y, const float z);
		virtual void setX(const float x);
		virtual void setY(const float y);
		virtual void setZ(const float z);
		virtual void setRotAngle(const float angle);

		virtual void draw(ResourceManager& rm);
		virtual btRigidBody& getBody();

		#warning ['TODO']: Make private
		void removeRigidBody_();

	protected:
		btCollisionShape* shape_; /**< The collision shape. */
		btCollisionObject* body_; /**< The collision body. */
		virtual void ProcessBody_();

	private:
		
		btDefaultMotionState* motionState_;
		btScalar mass_;
		btScalar friction_;
		btVector3 inertia_;
		
	
};

#endif /* TX_RIGIDBODY_HPP */
