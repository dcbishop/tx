#include "Location.hpp"

#include <limits>

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

/**
 * Gets the distance from this Location to another, if in different
 * Area's a large number is returned.
 * @param position The other position
 * @return The distance to the other position.
 */
float Location::getDistanceTo(Location* location) {
	// If they are in 2 different area, return a really large distance...
	if(location->getArea() != getArea()) {
		return std::numeric_limits<float>::max();
	} else {
		return Position::getDistanceTo(location);
	}
}
