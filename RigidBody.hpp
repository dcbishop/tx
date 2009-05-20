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
		virtual ~RigidBody();
		virtual Object* clone();
		virtual void setShape(btCollisionShape* shape);
		virtual btVector3& getPos();
		virtual const float getX();
		virtual const float getY();
		virtual const float getZ();
		virtual void setMass(const btScalar mass);
		virtual void setFriction(const btScalar friction);
		virtual void setXYZ(const float x, const float y, const float z);
		virtual void setX(const float x);
		virtual void setY(const float y);
		virtual void setZ(const float z);
		virtual void setRotX(const float x);
		virtual void setRotY(const float y);
		virtual void setRotZ(const float z);
		virtual void setRotAngle(const float angle);
		btCollisionShape* loadShapeFromModel(RigidBody* body);
		btCollisionShape* loadShapeBox(const float x, const float y, const float z);
		void disableRotation();
		void setKinematic();
		void stopMovement();
		virtual void draw(Interface* interface);
		virtual btRigidBody& getBody();

		virtual void addBody(Physics* physics);
		virtual void removeBody(Physics* physics);
		Physics* getPhysics();



	protected:
		void selfRemoveBody_();
		void selfAddBody_();
		btCollisionShape* shape_; /**< The collision shape. */
		btCollisionObject* body_; /**< The collision body. */
		virtual void processBody_();
		virtual void setRot_();


	private:
		void loadShapeFromModel_ProcessNode_(SceneNode* node, btCompoundShape* combined);
		btCollisionShape* loadShapeFromModel_ProcessNodes_(SceneNode* node, btCompoundShape* shape);
		btDefaultMotionState* motionState_;
		btScalar mass_;
		btScalar friction_;
		btVector3 inertia_;
		
	
};

#endif /* TX_RIGIDBODY_HPP */
