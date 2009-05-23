#include "VfxOffset.hpp"
#include <GL/gl.h>

VfxOffset::VfxOffset(float x, float y, float z) {
	setXYZ(x, y, z);
}

void VfxOffset::preDraw(Interface* interface) {
	glPushMatrix();
	glTranslatef(getX(), getY(), getZ());
}

void VfxOffset::postDraw(Interface* interface) {
	glPopMatrix();
}
