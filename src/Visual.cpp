#include "Visual.hpp"

#include "Interface.hpp"

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

void Visual::preDraw(Interface* interface) {
	if(!interface) {
		return;
	}
	for(vector<Vfx*>::iterator itr = effects_.begin(); itr != effects_.end(); itr++) {
		Vfx* vfx = (*itr);
		if(vfx) {
			vfx->preDraw(interface);
		}
	}
}

void Visual::postDraw(Interface* interface) {
	for(vector<Vfx*>::reverse_iterator itr = effects_.rbegin(); itr != effects_.rend(); itr++) {
		(*itr)->postDraw(interface);
	}
}

void Visual::addVfx(Vfx* vfx) {
	DEBUG_A("Adding vfx %p", vfx);
	//DEBUG_A(type(vfx))
	effects_.push_back(vfx);
}

void Visual::removeVfx(Vfx* vfx) {
	#warning ['TODO']: Remove effects...
	vector<Vfx*>::iterator found = find(effects_.begin(), effects_.end(), vfx);
	effects_.erase(found);
	#warning ['TODO']: delete vfx here?
}

void Visual::clearVfx() {
	#warning ['TODO']: Clear all effects...
}
