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
const float Location::getDistanceTo(Location& location) {
	// If they are in 2 different area, return a really large distance...
	if(location.getArea() != getArea()) {
		return std::numeric_limits<float>::max();
	}

	return Position::getDistanceTo(location);
}

/**
 * Gets the distance from this Location to another, ignoring height.
 * @param location The other Location
 * @return The distance to the other Location.
 */
const float Location::getDistanceTo2D(Location& location) {
	if(location.getArea() != getArea()) {
		return std::numeric_limits<float>::max();
	}

	return Position::getDistanceTo2D(location);
}

/**
 * Returns the X grid coordinate.
 * @return the X grid coordinate
 */
const int Location::getGridX() {
	if(!getArea()) {
		return -1;
	}

	int x, y;
	getArea()->getGridCoord(getX(), getZ(), x, y);
	return x;
}

/**
 * Returns the Y grid coordinate.
 * @return the Y grid coordinate
 */
const int Location::getGridY() {
	if(!getArea()) {
		return -1;
	}

	int x, y;
	getArea()->getGridCoord(getX(), getZ(), x, y);
	return y;
}
