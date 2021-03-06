#include "Area.hpp"
#include <stdlib.h>
#include <GL/gl.h>

#include "Tile.hpp"
#include "Object.hpp"
#include "RigidBody.hpp"
#include "GameManager.hpp"
#include "Interface.hpp"
#include "Light.hpp"

#include "console.h"

static const int MAX_LIGHTS = 8;

Area::Area(const string tag) {
	setTag(tag);
	height_ = 0;
	width_ = 0;
	tiles_ = NULL;
	clipbox_ = NULL;
	//clipbox_ = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
	walkblockers_ = NULL;
	//setDefaultArea();
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
				tiles_[x][y] = NULL;
				walkblockers_[x][y] = NULL;
			}
		}
	}

	float x_offset = (old_width - width_) * (TILEWIDTH / 2.0f);
	float z_offset = (old_height - height_) * (TILEWIDTH / 2.0f);
	for(ChildrenIterator iter = getChildBegin(); iter != getChildEnd(); iter++) {
		Object* object = dynamic_cast<Object*>(*iter);
		if(!object) {
			continue;
		}
		object->setX(object->getX() - x_offset);
		object->setZ(object->getZ() - z_offset);
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
void Area::setDefaultArea() {
	DEBUG_M("Entering function...");
	setSize(20, 20);

	fill(0, 0, width_-1, height_-1, TILE_VOID);
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
	tile->setParent(this);
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
	/*if(isSolid(x, y) && solid) {
		return;
	}*/

	if(!solid) {
		//RigidBody* blocker = *(walkblockers_+(y*width_)+x);
		RigidBody* blocker = walkblockers_[x][y];
		if(blocker) {
			//blocker->removeRigidBody_();
			//blocker->removeBody(getPhysics());
			#warning ['TODO']: This should delete the old blocker...
			delete(blocker);
		}
		//*(walkblockers_+(y*width_)+x) = NULL;
		walkblockers_[x][y] = NULL;
	}

	if(solid) {
		float fx,fz;
		getWorldCoord(x, y, fx, fz);
		RigidBody* blocker = new RigidBody("BLOCKER", NULL);
		blocker->setTempory(true);
		blocker->setShape(new btBoxShape(btVector3(0.5f, 0.5f, 0.5f)));
		blocker->setMass(0.0f);
		blocker->setXYZ(fx, 0.5f, fz);
		//*(walkblockers_+(y*width_)+x) = blocker;
		walkblockers_[x][y] = blocker;
		addObject(blocker);
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

	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	/* This was cut, attenuation never worked right for some reason...
	// Disable unused lights
	for(int i = 0; i < MAX_LIGHTS; i++) {
		glDisable(GL_LIGHT0 + i);
	}

	// Process lights
	int light = 0; // We want to skip the first light as its a global one...
	for(vector<Light*>::iterator iter = lights_.begin(); iter != lights_.end(); iter++) {
		if(light > MAX_LIGHTS) {
			break;
		}
		Light* pl = *iter;
		if(!pl) {
			ERROR("A Light that is Not a light...");
			continue;
		}
		glEnable(GL_LIGHT0 + light);

		// Set light position
		float position[] = {pl->getX(), pl->getY(), pl->getX(), pl->getDirectional()};
		glLightfv(GL_LIGHT0 + light, GL_POSITION, position);

		float argba[] = {pl->ambient.red, pl->ambient.green, pl->ambient.blue, pl->ambient.alpha};
		glLightfv(GL_LIGHT0+light, GL_AMBIENT, argba);

		float drgba[] = {pl->diffuse.red, pl->diffuse.green, pl->diffuse.blue, pl->diffuse.alpha};
		glLightfv(GL_LIGHT0+light, GL_DIFFUSE, drgba);

		float srgba[] = {pl->specular.red, pl->specular.green, pl->specular.blue, pl->specular.alpha};
		glLightfv(GL_LIGHT0+light, GL_SPECULAR, srgba);

		float ergba[] = {pl->emission.red, pl->emission.green, pl->emission.blue, pl->emission.alpha};
		glLightfv(GL_LIGHT0+light, GL_EMISSION, ergba);

		glLightf(GL_LIGHT0+light, GL_CONSTANT_ATTENUATION, pl->getConstantAttenuation());
		glLightf(GL_LIGHT0+light, GL_LINEAR_ATTENUATION, pl->getLinearAttenuation());
		glLightf(GL_LIGHT0+light, GL_QUADRATIC_ATTENUATION, pl->getQuadraticAttenuation());

		light++;
	}*/

	glPushMatrix();
	glTranslatef( TILEWIDTH * width_ / 2, 0.0f, TILEWIDTH * height_ / 2 );
	for(int y = 0; y < height_; y++) {
		glPushMatrix();
		for(int x = 0; x < width_; x++) {
			Tile* tile = getTile(x, y);
			if(tile) {
				if(interface->getEditMode() != MODE_NONE) {
					glEnable(GL_COLOR_MATERIAL);
					if(getSolid(x, y)) {
						glColor3f(1.0, 0.0, 0.0);
					} else {
						glColor3f(1.0, 1.0, 1.0);
					}
					tile->draw(interface);
				} else {
					tile->draw(interface);
				}
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
void Area::setPhysics(Physics* physics) {
	physics_ = physics;
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
void Area::addObject(Object* object) {
	//object->setArea(this);
	DEBUG_M("Entering function...");
	GameManager* gm = getGameManager();
	if(object->getGameManager() != gm) {
		DEBUG_A("Different GameMangers...");
		object->setGameManager(gm);
		if(gm) {
			DEBUG_A("Registering  object with gamemanager...");
			gm->registerObject(object);
		}
	}

	RigidBody* rb = dynamic_cast<RigidBody*>(object);
	if(rb) {
		rb->addBody(getPhysics());
	}

	Light* pl = dynamic_cast<Light*>(object);
	if(pl) {
		lights_.push_back(pl);
	}

	addChild(object);
}

/**
 * Remove an Object from the area.
 * @param object The Object's pointer.
 * @see addObject()
 */
void Area::removeObject(Object* object) {
	removeChild(object);
	RigidBody* rb = dynamic_cast<RigidBody*>(object);
	if(rb) {
		rb->removeBody(getPhysics());
	}
	GameManager* gm = getGameManager();
	if(gm) {
		gm->deregisterObject(object);
	}
	#warning ['TODO']: Remove lights...
}

/**
 * updates the Area based on the time.
 * @param time The current game time in milliseconds.
 */
void Area::update(const int time) {
	physics_->update(time);
	Updateable::update(time);
}

float Area::getAreaWorldWidth() {
	return getWidth() * TILEWIDTH;
}

float Area::getAreaWorldHeight() {
	return getHeight() * TILEWIDTH;
}

/**
 * Gets the x, y Area grid coordinates from OpenGL world coordinates.
 * @param fx The world X coordinate to be converted.
 * @param fz The world Z (depth) coordinate to be converted.
 * @param gx The value to store the X grid Coord in.
 * @param gy The value to store the Y grid Coord in.
 */
void Area::getGridCoord(const float fx, const float fz, int &gx, int &gy) {
	//fx = fx + getAreaWorldWidth()/2;
	//fz = fz + getAreaWorldWidth()/2;
	gx = (-fx+(getAreaWorldWidth()/2)-(TILEWIDTH/2)) / TILEWIDTH+1;
	gy = (-fz+(getAreaWorldHeight()/2)-(TILEWIDTH/2)) / TILEWIDTH+1;
	//gx = -((fx)+(TILEWIDTH/2)/TILEWIDTH)+(width_/2)+1;
	//gy = -((fz)+(TILEWIDTH/2)/TILEWIDTH)+(height_/2)+1;
}

/**
 * Gets the x, y world coordinates from Area grid world coordinates.
 * @param gx The Area grid X coordinate to be converted.
 * @param gy The Area grid Y coordinate to be converted.
 * @param fx The value to store the X world Coord in.
 * @param fz The value to store the Z (depth) world Coord in.
 */
void Area::getWorldCoord(const int gx, const int gy, float &fx, float &fz) {
	fx = -gx * TILEWIDTH+(width_*TILEWIDTH/2);
	fz = -gy * TILEWIDTH+(height_*TILEWIDTH/2);;
}

/**
 * Returns a location from the Area grid coords.
 * @param x The x grid coord.
 * @param y The y grid coord.
 * @return a Location
 */
Location Area::getLocationFromGridCoord(const int x, const int y) {
	float fx, fz;
	getWorldCoord(x, y, fx, fz);

	Location location;
	location.setArea(this);
	location.setXYZ(fx, 0.0, fz);
	return location;
}

/**
 * Returns a location from the cordinates.
 * @param x
 * @param y
 * @param z
 * @return The location.
 */
Location Area::getLocation(const float x, const float y, const float z) {
	Location location;
	location.setArea(this);
	location.setXYZ(x, y, z);
	return location;
}
