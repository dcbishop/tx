#include "VfxVisual.hpp"

#include <GL/gl.h>

VfxVisual::VfxVisual(Visual* visual) {
	visual_ = visual;
}

void VfxVisual::preDraw(Interface* interface) {
	if(!visual_) {
		return;
	}

	glPushMatrix();
	glTranslatef(getX(), getY(), getZ());
	glRotatef(getRotX(), getRotY(), getRotZ(), getRotAngle());
	visual_->draw(interface);
	glPopMatrix();
}
