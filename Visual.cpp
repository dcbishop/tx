#include "Visual.hpp"

Visual::Visual() {
	setVisible(true);
}

/*void draw(ResourceManager& rm) {
	// Dummy...
}*/

/**
 * Sets the visibility of the Visual model.
 * @param visible true for visible.
 */
void Visual::setVisible(const bool visible) {
	isVisible_ = visible;
}

/**
 * Returns the visiblity of the model.
 * @return true for visible.
 */
bool Visual::isVisible() {
	return isVisible_;
}
