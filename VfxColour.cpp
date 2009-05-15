#include "VfxColour.hpp"

#include "Interface.hpp"

VfxColour::VfxColour(float red, float green, float blue, float alpha) {
	red_ = red;
	green_ = green;
	blue_ = blue;
	alpha_ = alpha;
}

void VfxColour::preDraw(Interface* interface) {
	glEnable(GL_COLOR_MATERIAL);
	glColor4f(red_, green_, blue_, alpha_);
	DEBUG_A("Doings...");
}

void VfxColour::postDraw(Interface* interface) {
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_COLOR_MATERIAL);
	#warning ['TODO']: Maybe store original colour and reload it.
}

/**
 * Sets the colour to apply to the object.
 */
void VfxColour::setColour(float red, float green, float blue, float alpha) {
	red_ = red;
	green_ = green;
	blue_ = blue;
	alpha_ = alpha;
}
