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
class Creature : public RigidBody {
	public:
		Creature(string tag = DEFAULT_TAG, Model* model = NULL);
		~Creature();
		void Update(int time);
		
		virtual void Forward(bool state=true);
		virtual void Reverse(bool state=true);
		virtual void TurnLeft(bool state=true);
		virtual void TurnRight(bool state=true);
		virtual void StrafeLeft(bool state=true);
		virtual void StrafeRight(bool state=true);
		virtual void Jump();
		virtual void Run(bool state=true);

		virtual void setTurnRate(float turn_rate);
		virtual void setShape(btCollisionShape* shape);
		virtual void setArea(Area* area);
		virtual void setPos(float x, float y, float z);
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

#endif
