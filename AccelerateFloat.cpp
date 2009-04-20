/*
 * IDMP A Project
 * David C. Bishop - s3036687
 */
#warning ['TODO']: This file isnt needed...
#include "AccelerateFloat.hpp"
#include "console.h"

AccelerateFloat::AccelerateFloat() {
	value_ = 0.0f;
	value_max_ = 10.0f;
	value_min_ = 0.0f;
	acceleration_ = 0.0f;
	threshold_ = 0.01f;
	accelerating_ = true;
}

void AccelerateFloat::setMax(float max) {
	value_max_ = max;
}

void AccelerateFloat::setMin(float min) {
	value_min_ = min;
}

void AccelerateFloat::Accelerate(float amount) {
	acceleration_ = amount;
	accelerating_ = true;
}

void AccelerateFloat::Decelerate(float amount) {
	acceleration_ = -amount;
	accelerating_ = false;
}

void AccelerateFloat::setThreshold(float threshold) {
	threshold_ = threshold;
}

void AccelerateFloat::update(int time) {
	float diff = acceleration_ * (time - getLastupdate()) / 1000;
	Updateable::update(time);
	
	/* If we are at rest and not accelerating, do nothing */
	if(value_ == 0.0f && !accelerating_) {
		return;
	}

	/* If we are decelrating and within the threshold */
	if(!accelerating_ && (value_ < threshold_ || -value_ > -threshold_)) {
		value_ = 0.0f;
	}

	value_ += diff;

	if(value_ > value_max_) {
		value_ = value_max_;
	} else if (value_ < value_min_) {
		value_ = value_min_;
	}
}

float AccelerateFloat::getValue() {
	return value_;
}
