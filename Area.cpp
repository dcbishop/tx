#include "Area.hpp"
#include <stdlib.h>

#warning: TODO: remove this
#include <typeinfo>
#include <GL/gl.h>

#include "Tile.hpp"
#include "Object.hpp"
#include "RigidBody.hpp"
#include "GameManager.hpp"
#include "Interface.hpp"

#include "console.h"

Area::Area(const string tag) {
	setTag(tag);
	height_ = 0;
	width_ = 0;
	tiles_ = NULL;
	clipbox_ = NULL;
	//clipbox_ = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
	walkblockers_ = NULL;
}

/**
 * Area deconstructor, unloads all the tiles from memory.
 */
Area::~Area() {
	DEBUG_M("Entering function...");
	#warning ['TODO']: Delete objects?
	setSize(0, 0);
	delete [] tiles_;
	tiles_ = NULL;
	delete(clipbox_);
}

/**
 * @return the area's height in tiles.
 */
int Area::getHeight() {
	return height_;
}

/**
 * Resizes the area.
 * @param height The Area's new height in grid size.
 */
void Area::setHeight(float height) {
	setSize(getWidth(), height);
}

/**
 * Resizes the area.
 * @param width The Area's new width in grid size.
 */
void Area::setWidth(float width) {
	setSize(width, getHeight());
}

/**
 * @return the area's width in tiles.
 */
int Area::getWidth() {
	return width_;
}

void*** Area::regrowArray_(void*** array, int old_width, int old_height, int width, int height) {
	array = (void***)realloc(array, width * sizeof(void**));
	for(int x = old_width; x < width; x++) {
		array[x] = NULL;
	}

	for(int x = 0; x < width; x++) {
		DEBUG_M("AlPosition %d...", x);
		array[x] = (void**)realloc(array[x], height * sizeof(void*));
		for(int y = old_height; y < height; y++) {
			array[x][y] = NULL;
		}
	}

	return array;
}

/**
 * Sets the size of the area.
 * @param width The width.
 * @param height The heigh.
 */
void Area::setSize(int width, int height) {
	DEBUG_M("Entering function...");

	int old_width = width_;
	int old_height = height_;

#warning ['TODO']: Decide when tiles are unloaded
	DEBUG_H("\tUnloading dropped tiles...");
	// Unload any tiles that are dropped
	if(width < old_width) {
		DEBUG_H("\tWidth is less than old width, scrubbing lost tiles...");
		for(int y = 0; y < height; y++) {
			for(int x = old_width; x < width; x++) {
				delete getTile(x, y);
				setSolid(x, y, false);
			}
		}
	}
	if(height < old_height) {
		DEBUG_H("\tHeight is less than old width, scrubbing lost tiles...");
		for(int y = old_height; y < height; y++) {
			for(int x = 0; x < old_width; x++) {
				delete getTile(x, y);
				setSolid(x, y, false);
			}
		}
	}

	width_ = width;
	height_ = height;

	DEBUG_H("\tRealPosition tile space...");
	tiles_ = (Tile***)regrowArray_((void***)tiles_, old_width, old_height, width, height);
	DEBUG_H("\tRealPosition blocker space...");
	walkblockers_ = (RigidBody***)regrowArray_((void***)walkblockers_, old_width, old_height, width, height);

	// Realloc space for tiles
	//tiles_ = (Tile**)realloc(tiles_, width * height * sizeof(Tile*));
	//walkblockers_ = (RigidBody**)realloc(walkblockers_, width * height * sizeof(RigidBody*));
	DEBUG_H("\tAllocated...");

	// If we are freeing the Area
	if(!width || !height) {
		return;
	}

	if(!tiles_) {
		ERROR("Failed to allocate memory for tile map.");
		return;
	}

	#warning ['TODO']: This function should be split up some more, also shouldn't need to NULL tiles befoure setting them.
	// Set new tiles to default
	if(width > old_width) {
		DEBUG_H("\tWidth is > than old width, making new tiles...");
		for(int y = 0; y < height; y++) {
			for(int x = old_width; x < width; x++) {
				DEBUG_H("\t\tsetting %dx%d...", x, y);
				//setTile(x, y, NULL);
				/* *(tiles_+(y*width_)+x) = NULL;
				*(walkblockers_+(y*width_)+x) = NULL; */
				tiles_[x][y] = NULL;
				walkblockers_[x][y] = NULL;
			}
		}
	}
	if(height > old_height) {
		DEBUG_H("\theight is > than old height, making new tiles...");
		for(int y = old_height; y < height; y++) {
			for(int x = 0; x < width; x++) {
				DEBUG_H("\t\tsetting %dx%d...", x, y);
				//setTile(x, y, new Tile(TILE_VOID));
				//setTile(x, y, NULL);
				/* *(tiles_+(y*width_)+x) = NULL;
				*(walkblockers_+(y*width_)+x) = NULL; */
				tiles_[x][y] = NULL;
				walkblockers_[x][y] = NULL;
			}
		}
	}
	DEBUG_H("\tFunction finished, area now %d, %d...", getWidth(), getHeight());
}

/**
 * Fills an area with tiles.
 * @param x1 Start x coordinate.
 * @param y1 Start y coordinate.
 * @param x2 End x coordinate.
 * @param y2 End y coordinate.
 * @param filename Tile's model filename.
 * @param solidness The tile's solid state.
 * @param rotation Tile's rotation.
 */
void Area::fill(const int x1, const int y1, const int x2, const int y2, const string filename, const bool solidity, const float rotation) {
	for(int y = y1; y <= y2; y++) {
		for(int x = x1; x <= x2; x++) {
			setTile(x, y, new Tile(filename));
			setRotation(x, y, rotation);
			setSolid(x, y, solidity);
		}
	}
}

/**
 * For debugging, makes a square room on the map.
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 */
void Area::boxRoom(const int x1, const int y1, const int x2, const int y2) {
	// Floor
	fill(x1+1, y1+1, x2-1, y2-1, TILE_FLOOR);

	// Top side
	fill(x1+1, y1, x2-1, y1, TILE_WALL, true, -90.0f);

	// Left side
	fill(x1, y1+1, x1, y2-1, TILE_WALL, true);

	// Right side
	fill(x2, y1+1, x2, y2-1, TILE_WALL, true, 180.0f);

	// Bottom side
	fill(x1+1, y2, x2-1, y2, TILE_WALL, true, 90.0f);

	// TL
	setTile(x1, y1, new Tile(TILE_INNERCORNER));
	setRotation(x1, y1, -90.0f);
	setSolid(x1, y1);

	// BL
	setTile(x1, y2, new Tile(TILE_INNERCORNER));
	setSolid(x1, y2);

	// TR
	setTile(x2, y1, new Tile(TILE_INNERCORNER));
	setRotation(x2, y1, -180.0f);
	setSolid(x2, y1);

	// BR
	setTile(x2, y2, new Tile(TILE_INNERCORNER));
	setRotation(x2, y2, 90.0f);
	setSolid(x2, y2);
}

#warning ['TODO']: Actually load the area from a file (or remove this).
/**
 * Load the area from a file.
 * @param filename
 */
void Area::loadFile(const string filename) {
	DEBUG_M("Entering function...");
	setSize(20, 20);

#warning ['TODO']: Do this...
	boxRoom(3, 3, 13, 13);

	/*FILE* fp;
	mxml_node_t *tree;
	fp = fopen(filename.c_str(), "r");
	tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);
	fclose(fp);

	mxmlDelete(tree);*/
}

/**
 * @see setTile()
 * @param x The X grid coordinate.
 * @param y The X grid coordinate.
 * @return The Tile at the x, y grid coordinates
 */
Tile* Area::getTile(const int x, const int y) {
	if(x >= getWidth() || y >= getHeight() || x < 0 || y < 0) {
		return NULL;
	} 
	//return *(tiles_+(y*width_)+x);
	return tiles_[x][y];
}

/**
 * @see setTile()
 * @param x The X grid coordinate.
 * @param y The X grid coordinate.
 * @param tile The tile.
 */
void Area::setTile(const int x, const int y, Tile* tile) {
	if(x >= getWidth() || y >= getHeight() || x < 0 || y < 0) {
		return;
	}

	Tile* current = getTile(x, y);
	delete current;
	//*(tiles_+(y*width_)+x) = tile;
	tiles_[x][y] = tile;
}

/**
 * Sets if a tile is solid or not.
 * @param x The X grid coordinate.
 * @param y The Y grid coordinate.
 * @param solid If true the tile is solid.
 * @see isSolid()
 */
void Area::setSolid(const int x, const int y, const bool solid) {
	if(x >= getWidth() || y >= getHeight() || x < 0 || y < 0) {
		return;
	}

	// Already solid...
	if(isSolid(x, y) && solid) {
		return;
	}

	if(!solid) {
		//RigidBody* blocker = *(walkblockers_+(y*width_)+x);
		RigidBody* blocker = walkblockers_[x][y];
		if(blocker) {
			blocker->removeRigidBody_();
		}
		//*(walkblockers_+(y*width_)+x) = NULL;
		walkblockers_[x][y] = NULL;
	}

	if(solid) {
		float fx,fz;
		getWorldCord(x, y, fx, fz);
		RigidBody* blocker = new RigidBody("BLOCKER", NULL);
		blocker->setTempory(true);
		blocker->setShape(new btBoxShape(btVector3(0.5f, 0.5f, 0.5f)));
		blocker->setMass(0.0f);
		blocker->setXYZ(fx, 0.5f, fz);
		//*(walkblockers_+(y*width_)+x) = blocker;
		walkblockers_[x][y] = blocker;
		addObject(*blocker);
	}
}

/**
 * Sets the rotation of a tile
 * @param x The X grid coordinate.
 * @param y The Y grid coordinate.
 * @param rotation The rotation in deg.
 * @see getRotation()
 */
void Area::setRotation(const int x, const int y, float rotation) {
	Tile* tile = getTile(x, y);
	if(!tile) {
		return;
	}
	tile->setRotation(rotation);
}

/**
 * Gets the rotation of a tile
 * @param x The X grid coordinate.
 * @param y The Y grid coordinate.
 * @see setRotation()
 */
float Area::getRotation(const int x, const int y) {
	Tile* tile = getTile(x, y);
	if(!tile) {
		return 0.0f;
	}
	return tile->getRotation();
}

/**
 * Gets the RigidBody that is used to clip walking on the areas tile.
 * @param x The X grid coordinate.
 * @param y The Y grid coordinate.
 * @return The RigidBody or NULL if there is no blocker.
 */
RigidBody* Area::getSolid(const int x, const int y) {
	if(x >= getWidth() || y >= getHeight() || x < 0 || y < 0) {
		return NULL;
	}
	//return *(walkblockers_+(y*width_)+x);
	return walkblockers_[x][y];
}

/**
 * Checks if a tile is solid or not.
 * @param x The X grid coordinate.
 * @param y The Y grid coordinate.
 * @see setSolid()
 */
bool Area::isSolid(const int x, const int y) {
	if(x >= getWidth() || y >= getHeight() || x < 0 || y < 0) {
		return true;
	}

	return getSolid(x, y);
}

/**
 * Renders the area and all its objects.
 * @param rm The resource manager to use to manage models and images.
 */
void Area::draw(Interface* interface) {
#warning ['TODO']: Delete me....
	ResourceManager* rm = interface->getResourceManager();
	if(!rm) {
		return;
	}

	glPushMatrix();
	glTranslatef( TILEWIDTH * width_ / 2, 0.0f, TILEWIDTH * height_ / 2 );
	for(int y = 0; y < height_; y++) {
		glPushMatrix();
		for(int x = 0; x < width_; x++) {
			Tile* tile = getTile(x, y);
			if(tile) {
				tile->draw(interface);
			}
			glTranslatef(-TILEWIDTH, 0.0f, 0.0f);
		}
		glPopMatrix();
		glTranslatef(0.0f, 0.0f, -TILEWIDTH);
	}
	glPopMatrix();

	// draw all the objects in the map
	for(vector<Contained*>::iterator iter = children_.begin(); iter != children_.end(); iter++) {
		Visual* object = dynamic_cast<Visual*>(*iter);
		if(object) {
			object->draw(interface);
		}
	}
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
	physics_ = &physics;
	//processWalkmap_();
}

/**
 * Get GameManager.
 * @return The GameManager or NULL.
 */
/*GameManager* Area::getGameManager() {
	return dynamic_cast<GameManager*>(getParent());
}*/

/**
 * Adds an Object to the area.
 * @param object The Object's pointer.
 * @see removeObject()
 */
void Area::addObject(Object& object) {
	object.setArea(*this);
	object.setGameManager(getGameManager());
	GameManager* gm = getGameManager();
	if(gm) {
		gm->registerObject(object);
	}
	addChild(&object);
}

/**
 * Remove an Object from the area.
 * @param object The Object's pointer.
 * @see addObject()
 */
void Area::removeObject(Object& object) {
	removeChild(&object);
}

/**
 * updates the Area based on the time.
 * @param time The current game time in milliseconds.
 */
void Area::update(const int time) {
	//physics_->update(time);
	Updateable::update(time);
}

/**
 * Gets the x, y Area grid coordinates from OpenGL world coordinates.
 * @param fx The world X coordinate to be converted.
 * @param fz The world Z (depth) coordinate to be converted.
 * @param gx The value to store the X grid cord in.
 * @param gy The value to store the Y grid cord in.
 */
void Area::getGridCord(const float fx, const float fz, int &gx, int &gy) {
	gx = -((fx-(TILEWIDTH/2))/TILEWIDTH)+(width_/2);
	gy = -((fz-(TILEWIDTH/2))/TILEWIDTH)+(height_/2);
}

/**
 * Gets the x, y world coordinates from Area grid world coordinates.
 * @param gx The Area grid X coordinate to be converted.
 * @param gy The Area grid Y coordinate to be converted.
 * @param fx The value to store the X world cord in.
 * @param fz The value to store the Z (depth) world cord in.
 */
void Area::getWorldCord(const int gx, const int gy, float &fx, float &fz) {
	fx = -gx * TILEWIDTH+(width_*TILEWIDTH/2);
	fz = -gy * TILEWIDTH+(height_*TILEWIDTH/2);;
}
