#include "Creature.hpp"
#include <math.h>

Creature::Creature() {
	setAcceleration(5.0f);
	setTurnRate(180.0f);
	setSpeed(20.0f);
	setSpeedReverse(5.0f);
	setDeceleration(20.0f);
}

void Creature::setAcceleration(float acceleration) {
	acceleration_ = acceleration;
}

void Creature::setDeceleration(float decelration) {
	deceleration_ = decelration;
}

void Creature::setTurnRate(float turn_rate) {
	spin_.setMin(-turn_rate);
	spin_.setMax(turn_rate);
	turn_rate_ = turn_rate;
}

void Creature::setSpeed(float speed) {
	speed_.setMax(speed);
}

void Creature::setSpeedReverse(float speed_reverse) {
	speed_.setMin(-speed_reverse);
}

void Creature::Foward() {
	speed_.Accelerate(acceleration_);
}

void Creature::Reverse() {
	speed_.Accelerate(-acceleration_);
}

void Creature::Stop() {
	speed_.Decelerate(deceleration_);
}

void Creature::TurnLeft() {
	spin_.Accelerate(turn_rate_);
}

void Creature::TurnRight() {
	spin_.Accelerate(-turn_rate_);
}

void Creature::TurnStop() {
	spin_.Decelerate(999.0f);
}

void Creature::Update(int time) {
	speed_.Update(time);
	spin_.Update(time);
	int time_diff = time - getLastUpdate();
	setRotAngle(getRotAngle() + (spin_.getValue() * time_diff / 1000));

	float zdiff = cos(getRotAngle() * PI/180.0f) * speed_.getValue() * time_diff / 1000;
	float xdiff = sin(getRotAngle() * PI/180.0f) * speed_.getValue() * time_diff / 1000;
	setZ(getZ() + zdiff);
	setX(getX() + xdiff);

	Object::Update(time);
}
