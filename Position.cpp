#include "Position.hpp"

/**
 * Returns the Position.
 * @return Refrence to the Position.
 */
Position& Position::getPosition() {
	return *this;
}

/**
 * Sets the Position.
 * @param
 */
void Position::setPosition(Position& Position) {
	setXYZ(Position.getX(), Position.getY(), Position.getZ());
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
void Position::setXYZ(const float x, const float y, const float z) {
	Position::setX(x);
	Position::setY(y);
	Position::setZ(z);
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
const float Position::getX() {
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
const float Position::getY() {
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
const float Position::getZ() {
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
void Position::setX(const float x) {
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
void Position::setY(const float y) {
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
void Position::setZ(const float z) {
	z_ = z;
}
