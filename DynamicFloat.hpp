#ifndef TX_DYNAMICFLOAT_HPP
#define TX_DYNAMICFLOAT_HPP

#include "Updateable.hpp"

/**
 * A floating point number that changes with time to reach a target value.
 */
class DynamicFloat : public Updateable {
	public:
		DynamicFloat();
		float getValueCurrent();
		float getValueTarget();
		void setValue(const float value);
		void setRate(const float value);
		void setThreshold(const float value);
		void update(const int time);

	private:
		float value_target_;
		float value_current_;
		float value_rate_;
		float value_threshold_;
};

#endif /* TX_DYNAMICFLOAT_HPP */
