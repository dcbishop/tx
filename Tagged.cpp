#include "Tagged.hpp"
#include "GameManager.hpp"

/**
 * The constructor.
 * @param tag The objects tag.
 */
Tagged::Tagged(string tag)
{
	setTag(tag);
	gm_ = NULL;
}

/**
 * Returns the tag of the object.
 * @see setTag()
 * @return The object's tag.
 */
const string Tagged::getTag() {
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

/**
 * Gets the GameManager that manages this object.
 * @return The pointer to the GameManager or NULL.
 */
GameManager* Tagged::getGameManager() {
	return gm_;
}

/**
 * Sets the GameManager to manage this object.
 * @param gm The GameManager.
 */
void Tagged::setGameManager(GameManager* gm) {
	gm_ = gm;
}
