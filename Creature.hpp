#ifndef TX_CREATURE_HPP
#define TX_CREATURE_HPP

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h>
#include <BulletCollision/CollisionShapes/btConvexShape.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>

#include "Camera.hpp"
#include "Object.hpp"
#include "RigidBody.hpp"
#include "AccelerateFloat.hpp"

/**
 * A controllable creature.
 */
class Creature : public RigidBody, public Container {
	public:
		Creature(const string tag = DEFAULT_TAG, Visual* model = NULL);
		~Creature();
		virtual void update(const int time);
		virtual Object* clone();
		virtual void Forward(const bool state=true);
		virtual void Reverse(const bool state=true);
		virtual void TurnLeft(const bool state=true);
		virtual void TurnRight(const bool state=true);
		virtual void StrafeLeft(const bool state=true);
		virtual void StrafeRight(const bool state=true);
		virtual void Jump();
		virtual void Run(const bool state=true);

		virtual void setTurnRate(const float turn_rate);
		virtual void setShape(btCollisionShape* shape);
		virtual void setArea(Area& area);
		virtual void setXYZ(const float x, const float y, const float z);
		virtual btVector3& getPos();

	private:
		btKinematicCharacterController* controller_;
		btPairCachingGhostObject* controller_ghost_;

		float turn_rate_;
		bool turn_left_;
		bool turn_right_;
		bool forward_;
		bool backward_;
		bool strafe_left_;
		bool strafe_right_;
		bool running_;
		float turn_angle_;
		float walk_velocity_;
		float running_multiplier_;
};

#endif /* TX_CREATURE_HPP */
