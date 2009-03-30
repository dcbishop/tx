#include "DynamicFloat.hpp"
#include "console.h"

DynamicFloat::DynamicFloat() {
	value_current_ = 0.0f;
	value_target_ = 0.0f;
	value_rate_ = 1.0f;
	value_threshold_ = 0.01f;
	last_updated_ = 0;
}

float DynamicFloat::getValueCurrent() {
	return value_current_;
}

float DynamicFloat::getValueTarget() {
	return value_target_;
}

void DynamicFloat::setValue(const float value) {
	DEBUG_A("Set value to: %f", value);
	value_target_ = value;

	/* If this is the initial setting */
	if(last_updated_ == 0) {
		value_current_ = value;
	}
}

void DynamicFloat::setThreshold(const float threshold) {
	value_threshold_ = threshold;
}

void DynamicFloat::setRate(const float rate) {
	value_rate_ = rate;
}

void DynamicFloat::Update(const int time) {
	/* Process a smooth zoom */
	if(value_target_ != value_current_) {
		float value_diff = value_target_ - value_current_;
		float value_change = value_diff * value_rate_ * (time - last_updated_) / 1000;

		value_current_ += value_change;

		if(value_diff < 0) {
			value_diff*=-1;
		}

		if(value_diff <= value_threshold_) {
			value_current_ = value_target_;
		}
	}
	last_updated_ = time;
}
