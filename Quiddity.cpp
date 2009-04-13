#include "Quiddity.hpp"

/**
 * The constructor.
 * @param tag The objects tag.
 */
Quiddity::Quiddity(string tag)
{
	setTag(tag);
}

/**
 * Returns the tag of the object.
 * @see setTag()
 * @return The object's tag.
 */
string Quiddity::getTag() {
	return tag_;
}

/**
 * Returns the tag of the object.
 * @see getTag()
 * @param tag The object's tag.
 */
void Quiddity::setTag(string tag) {
	tag_ = tag;
}
