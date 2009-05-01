#include "Tile.hpp"
#include "Area.hpp"

#include "Interface.hpp"

Tile::Tile(const string filename) {
	setFilename(filename);
	rotation_ = 0.0f;
	clip_ = NULL;
}

Tile::~Tile() {
	removeRigidBody_();
	delete(clip_);
}

/**
 * Gets the area the tile is in.
 * @return The area or NULL.
 */
Area* Tile::getArea() {
	return dynamic_cast<Area*>(getParent());
}

void Tile::removeRigidBody_() {
	Area* area = getArea();
	if(clip_ && area && area->getPhysics() && area->getPhysics()->getWorld()) {
		area->getPhysics()->getWorld()->removeRigidBody(clip_);
	}
}

void Tile::addRigidBody_() {
	Area* area = getArea();
	if(clip_ && area && area->getPhysics() && area->getPhysics()->getWorld()) {
		area->getPhysics()->getWorld()->addRigidBody(clip_);
	}
}


/**
 * Sets if the tile can be walked through.
 * @param solid true for a solid tile.
 */
/*void Tile::setSolid(btRigidBody* clip) {
	removeRigidBody_();
	delete(clip_);
	clip_ = clip;
	addRigidBody_();
}*/

/**
 * Gets the bullet rigid body of the tile clipping.
 * @return The bullet rigid body.
 */
/*btRigidBody* Tile::getSolid() {
	return clip_;
}*/

/**
 * Sets rotation on a tile.
 * @param rotation The angle of rotation.
 * @see getRotation()
 */
void Tile::setRotation(float rotation) {
	rotation_ = rotation;
}

/**
 * Gets the tiles rotation.
 * @return The rotation of the tile around the Y axis.
 * @see setRotation()
 */
float Tile::getRotation() {
	return rotation_;
}

void Tile::draw(Interface* interface) {
	if(!isVisible()) {
		return;
	}

	ResourceManager* rm = interface->getResourceManager();
	if(!rm) {
		return;
	}

	Model* model = rm->loadModel(getFilename());

	// Debugging, draw solid tiles red...
	/*if(getSolid()) {
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1.0f, 0.0f, 0.0f);
	}*/

	glPushMatrix();
	glRotatef(rotation_, 0.0f, 1.0f, 0.0f);
	RCBC_Render(model);
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}
