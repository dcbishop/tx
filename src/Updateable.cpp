#include "Updateable.hpp"

Updateable::Updateable(): last_update_(0) {};

/**
 * updates the object with time.
 * @param time The current game time in milliseconds.
 */
void Updateable::update(const int time) {
	last_update_ = time;
}

/**
 * Gets the last time the last update occured.
 * @return The last update time in milliseconds.
 */
const int Updateable::getLastupdate() {
	return last_update_;
}
