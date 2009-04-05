#ifndef TX_CREATURE_HPP
#define TX_CREATURE_HPP

#include "Camera.hpp"
#include "Object.hpp"
#include "AccelerateFloat.hpp"

class Creature : public Object {
	public:
		Creature();
		void Foward();
		void Reverse();
		void Stop();
		void TurnLeft();
		void TurnRight();
		void TurnStop();
		void Update(int time);

		void setAcceleration(float acceleration);
		void setDeceleration(float decelration);
		void setTurnRate(float turn_rate);
		void setSpeed(float speed);
		void setSpeedReverse(float speed_reverse);
	
	private:
		AccelerateFloat speed_;
		AccelerateFloat spin_;
		float acceleration_;
		float deceleration_;
		float turn_rate_;
};

#endif
