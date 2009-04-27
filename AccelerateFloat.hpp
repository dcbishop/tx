#warning ['TODO']: This file isnt needed...
#ifndef TX_ACCELERATEFLOAT_HPP
#define TX_ACCELERATEFLOAT_HPP

#include "Updateable.hpp"

/**
 * A floating point number that changes with time at an increasing rate.
 * Useable for acceleration. This is no longer used.
 */
class AccelerateFloat : public Updateable {
	public:
		AccelerateFloat();
		void Accelerate(float amount);
		void Decelerate(float amount);
		void update(int time);
		void setMax(float max);
		void setMin(float min);
		void setThreshold(float threshold);
		float getValue();

	private:
		float value_;
		float value_max_;
		float value_min_;
		float acceleration_;
		float threshold_;
		bool accelerating_;
};

#endif /* TX_ACCELERATEFLOAT_HPP */
