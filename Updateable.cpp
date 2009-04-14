#include "Updateable.hpp"

Updateable::Updateable(): last_update_(0) {};

/**
 * Updates the object with time.
 * @param time The current game time in milliseconds.
 */
void Updateable::Update(const int time) {
	last_update_ = time;
}

/**
 * Gets the last time the last update occured.
 * @return The last update time in milliseconds.
 */
const int Updateable::getLastUpdate() {
	return last_update_;
}
