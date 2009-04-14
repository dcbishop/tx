#include "Tagged.hpp"

/**
 * The constructor.
 * @param tag The objects tag.
 */
Tagged::Tagged(string tag)
{
	setTag(tag);
}

/**
 * Returns the tag of the object.
 * @see setTag()
 * @return The object's tag.
 */
string Tagged::getTag() {
	return tag_;
}

/**
 * Returns the tag of the object.
 * @see getTag()
 * @param tag The object's tag.
 */
void Tagged::setTag(const string tag) {
	tag_ = tag;
}
