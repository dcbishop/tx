#include "Container.hpp"

/**
 * Makes the container contain a thing.
 * @param child The thing to be contained.
 */
void Container::addChild(Contained* child) {
	if(child) {
		child->setParent(this);
		children_.push_back(child);
	}
}

/**
 * Sets the parent/owner Container.
 * @param parent The thing within which this thing is contained.
 */
void Contained::setParent(Container* parent) {
	parent_ = parent;
}

/**
 * Gets the parent/owning Container of the thing.
 * @return Pointer to the parent Container.
 */
Container* Contained::getParent() {
	return parent_;
}
