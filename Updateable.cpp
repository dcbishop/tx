#include "Updateable.hpp"

Updateable::Updateable(): last_update_(0) {};

/**
 * Updates the object with time.
 * @param time The current time.
 */
void Updateable::Update(const int time) {
	last_update_ = time;
}

/**
 * Gets the last time the last update occured.
 * @return The last update time.
 */
const int Updateable::getLastUpdate() {
	return last_update_;
}
