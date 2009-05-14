#include "Location.hpp"

/**
 * Gets the current location.
 * @return The Location.
 */
Location& Location::Location::getLocation() {
	return *this;
}

/**
 * Sets the Location information.
 * @param location The location.
 */
void Location::setLocation(Location& location) {
	setPosition(location.getPosition());
	setArea(*location.getArea());
	setRotation(location.getRotation());
}


/**
 * Puts the object in an area.
 * @see getArea()
 */
void Location::setArea(Area& area) {
	DEBUG_M("Entering function...");
	setParent(&area);
}

/**
 * Returns the object's area.
 * @see setArea()
 * @return The area contining the object.
 */
Area* Location::getArea() {
	return dynamic_cast<Area*>(getParent());
}
