#include "Area.hpp"
#include <stdlib.h>

#warning: TODO: remove this
#include <typeinfo>
#include <GL/gl.h>


#include "console.h"

Area::Area() {
	height_ = 0;
	width_ = 0;
}

/**
 * @return the area's height in tiles.
 */
int Area::getHeight() {
	return height_;
}

/**
 * @return the area's width in tiles.
 */
int Area::getWidth() {
	return width_;
}

#warning ['TODO']: Actually load the area from a file.
/**
 * Load the area from a file.
 * @param filename
 */
void Area::LoadFile(const string filename) {
	DEBUG_M("Entering function...");
	height_ = 100;
	width_ = 100;
	
	tiles_ = (Model**)malloc(width_ * height_ * sizeof(Model*));
	if(!tiles_) {
		ERROR("Failed to allocate memory for tile map.");
		return;
	}
	
	Model* grass = RCBC_LoadFile("data/models/mayagrass.dae", rm_->getImages());
	Model* monkey = RCBC_LoadFile("data/models/monkey-test.dae", rm_->getImages());
	
	for(int y = 0; y < height_; y++) {
		for(int x = 0; x < width_; x++) {
			setTile(x, y, grass);
		}
	}
	setTile(0, 0, monkey);
	setTile(1, 0, monkey);
	setTile(4, 4, monkey);
	setTile(2, 7, monkey);
}

/**
 * @see setTile()
 * @param x The X grid coordinate.
 * @param y The X grid coordinate.
 * @return The Tile at the x, y grid cordinates
 */
Tile* Area::getTile(const int x, const int y) {
	if(x > getWidth() || y > getHeight() || x < 0 || y < 0) {
		return NULL;
	} 
	return *(tiles_+(y*width_)+x);
}

/**
 * @see setTile()
 * @param x The X grid coordinate.
 * @param y The X grid coordinate.
 * @param tile The tile.
 */
void Area::setTile(const int x, const int y, Tile* tile) {
	if(x > getWidth() || y > getHeight() || x < 0 || y < 0) {
		return;
	}
	*(tiles_+(y*width_)+x) = tile;
}

/**
 * Renders the area and all its objects.
 */
void Area::Draw() {
#warning ['TODO']: Delete me....
	//glTranslatef( -TILEWIDTH * width_ / 2, 0.0f, -TILEWIDTH * height_ / 2 );
	glPushMatrix();
	for(int y = 0; y < height_; y++) {
		glPushMatrix();
		for(int x = 0; x < width_; x++) {
			Model* tile = getTile(x, y);
			DEBUG_M("FlagG 1...");

			RCBC_Render(tile);
			DEBUG_M("FlagG 2...");
			glTranslatef(-TILEWIDTH, 0.0f, 0.0f);
		}
		glPopMatrix();
		glTranslatef(0.0f, 0.0f, -TILEWIDTH);
	}
	glPopMatrix();

	// Draw all the objects in the map
	for(vector<Object*>::iterator iter = objects_.begin(); iter != objects_.end(); iter++) {
		(*iter)->Draw();
	}
}

/**
 * Sets the resource manager that this area will use.
 * @param rm The resource manager.
 * @see getResourceManager()
 */
void Area::setResourceManager(ResourceManager& rm) {
	DEBUG_M("Entering function...");
	rm_ = &rm;
}

/**
 * Gets the resource manager that this area uses.
 * @return The resource manager.
 * @see setResourceManager()
 */
ResourceManager* Area::getResourceManager() {
	return rm_;
}

/**
 * @return The physics engine the area uses.
 * @see setPhysics()
 */
Physics* Area::getPhysics() {
	return physics_;
}

/**
 * Sets the physics engine for the are to use.
 * @param physics The Physics engine pointer.
 */
void Area::setPhysics(Physics& physics) {
	DEBUG_M("Entering function...");
	physics_ = &physics;
}

Area::~Area() {
	DEBUG_M("Entering function...");
	#warning ['TODO']: Delete objects?
	delete [] tiles_;
	tiles_ = NULL;
}

/**
 * Adds an Object to the area.
 * @param object The Object's pointer.
 * @see removeObject()
 */
void Area::addObject(Object& object) {
	objects_.push_back(&object);
	object.setArea(*this);
}

/**
 * Remove an Object from the area.
 * @param object The Object's pointer.
 * @see addObject()
 */
void Area::removeObject(Object& object) {
	vector<Object*>::iterator iter;
	iter = find(objects_.begin(), objects_.end(), &object);

	if(iter != objects_.end()) {
		objects_.erase(iter);
	}
}

/**
 * Updates the Area based on the time.
 * @param time The current game time in milliseconds.
 */
void Area::Update(const int time) {
	DEBUG_M("FlagZ 1...");
	physics_->Update(time);
	Updateable::Update(time);
}
