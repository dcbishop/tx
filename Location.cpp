#include "Location.hpp"

/**
 * Returns the location.
 * @return Refrence to the Location.
 */
Location& Location::getLocation() {
	return *this;
}

/**
 * Sets the location.
 * @param
 */
void Location::setLocation(Location& location) {
	setXYZ(location.getX(), location.getY(), location.getZ());
}

/**
 * Sets the objects X, Y, Z coordinates .
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param z Z coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 */
void Location::setXYZ(const float x, const float y, const float z) {
	Location::setX(x);
	Location::setY(y);
	Location::setZ(z);
}

/**
 * Returns the current X coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @return The X coordinate.
 */
const float Location::getX() {
	return x_;
}

/**
 * Returns the current Y coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @return The Y coordinate.
 */
const float Location::getY() {
	return y_;
}

/**
 * Returns the current Z coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @return The Z coordinate.
 */
const float Location::getZ() {
	return z_;
}

/**
 * Sets the current X coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @param x the X coordinate
 */
void Location::setX(const float x) {
	x_ = x;
}

/**
 * Sets the current Y coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @param x the Y coordinate
 */
void Location::setY(const float y) {
	y_ = y;
}

/**
 * Sets the current Z coordinate.
 * @see setXYZ()
 * @see setX()
 * @see setY()
 * @see setZ()
 * @see getX()
 * @see getY()
 * @see getZ()
 * @param x the Z coordinate
 */
void Location::setZ(const float z) {
	z_ = z;
}
