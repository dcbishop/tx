#warning ['TODO']: This file isnt needed...
#ifndef TX_ACCELERATEFLOAT_HPP
#define TX_ACCELERATEFLOAT_HPP

/* A floating point number that changes with time to reach a target */
class AccelerateFloat {
	public:
		AccelerateFloat();
		void Accelerate(float amount);
		void Decelerate(float amount);
		void Update(int time);
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
		int last_updated_;
		bool accelerating_;
};

#endif
