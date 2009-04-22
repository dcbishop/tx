#include "Area.hpp"
#include <stdlib.h>

#warning: TODO: remove this
#include <typeinfo>
#include <GL/gl.h>

#include "Tile.hpp"
#include "Object.hpp"
#include "RigidBody.hpp"
#include "GameManager.hpp"

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

/**
 * Sets the size of the area.
 * @param width The width.
 * @param height The heigh.
 */
void Area::setSize(int width, int height) {
	DEBUG_M("Entering function...");

	int old_width = width_;
	int old_height = height_;
	width_ = width;
	height_ = height;

#warning ['TODO']: Decide when tiles are unloaded
	// Unload any tiles that are dropped
	if(width < old_width) {
		for(int y = 0; y < height; y++) {
			for(int x = old_width; x < width; x++) {
				//rm_->unloadModel(getTile(x, y));
				delete getTile(x, y);
				setSolid(x, y, false);
			}
		}
	}
	if(height < old_height) {
		for(int y = old_height; y < height; y++) {
			for(int x = 0; x < old_width; x++) {
				//rm_->unloadModel(getTile(x, y));
				delete getTile(x, y);
				setSolid(x, y, false);
			}
		}
	}

	// Realloc space for tiles
	tiles_ = (Tile**)realloc(tiles_, width * height * sizeof(Tile*));
	walkblockers_ = (RigidBody**)realloc(walkblockers_, width * height * sizeof(RigidBody*));

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
		for(int y = 0; y < height; y++) {
			for(int x = old_width; x < width; x++) {
				//Model* defaulttile = rm_->loadModel("data/models/mayagrass.dae");
				Tile* defaulttile = new Tile("data/models/void.dae");
				defaulttile->setParent(this);
				setTile(x, y, NULL);
				setTile(x, y, defaulttile);
				*(walkblockers_+(y*width_)+x) = NULL;
			}
		}
	}
	if(height > old_height) {
		for(int y = old_height; y < height; y++) {
			for(int x = 0; x < old_width; x++) {
				//Model* defaulttile = rm_->loadModel("data/models/mayagrass.dae");
				Tile* defaulttile = new Tile("data/models/void.dae");
				defaulttile->setParent(this);
				setTile(x, y, NULL);
				setTile(x, y, defaulttile);
				*(walkblockers_+(y*width_)+x) = NULL;
			}
		}
	}
}

/**
 * For debugging, makes a square room on the map.
 */
void Area::boxRoom(int start_x, int start_y, int size) {
	//int start_x = 5;
	//int start_y = 5;
	int width = size;
	int height = size;
	
	Tile* voidtile = new Tile("data/models/void.dae");
	Tile* wall;
	
	wall = new Tile("data/models/floor.dae");
	for(int y = start_y+1; y < start_y+height; y++) {
		for(int x = start_x+1; x < start_x+width; x++) {
			setTile(x, y, wall);
		}
	}
	for(int y = start_x; y < start_x+width; y++ ) {
		// Left side
		wall = new Tile("data/models/Wall.dae");
		setTile(start_x, y, wall);
		setSolid(start_x, y, true);
		
		// Right side
		wall = new Tile("data/models/Wall.dae");
		wall->setRotation(180.0f);
		setTile(start_x+width, y, wall);
		setSolid(start_x+width, y, true);
		
		// Top
		wall = new Tile("data/models/Wall.dae");
		wall->setRotation(-90.0f);
		setTile(y, start_y, wall);
		setSolid(y, start_y, true);
		
		// Bottom
		wall = new Tile("data/models/Wall.dae");
		wall->setRotation(90.0f);
		setTile(y, start_x + height, wall);
		setSolid(y, start_x + height, true);		
	}

	// TL
	wall = new Tile("data/models/inner corner.dae");
	wall->setRotation(-90.0f);
	setTile(start_x, start_x, wall);
	
	// BL
	wall = new Tile("data/models/inner corner.dae");
	//wall->setRotation(-90.0f);
	setTile(start_x, start_y+height, wall);
	
	// TR
	wall = new Tile("data/models/inner corner.dae");
	wall->setRotation(-180.0f);
	setTile(start_x+width, start_y, wall);
	
	// BR
	wall = new Tile("data/models/inner corner.dae");
	wall->setRotation(90.0f);
	setTile(start_x+width, start_y+height, wall);
}

#warning ['TODO']: Actually load the area from a file.
/**
 * Load the area from a file.
 * @param filename
 */
void Area::loadFile(const string filename) {
	DEBUG_M("Entering function...");
	setSize(20, 20);

	/*Model* grass = rm_->loadModel("data/models/mayagrass.dae");
	Model* monkey = rm_->loadModel("data/models/monkey-test.dae");*/
	//VModel* grass = new VModel("data/models/mayagrass.dae");
	
	boxRoom(3, 3, 10);


	/*for(int y = 0; y < height_; y++) {
		for(int x = 0; x < width_; x++) {
			setTile(x, y, grass);
		}
	}*/
	


	// Some Pillars
	/*wall = new Tile("data/models/Pillar.dae");
	setTile(5, 7, wall);
	setSolid(5, 7, true);

	setTile(7, 5, wall);
	setSolid(7, 5, true);
	
	setTile(12, 6, wall);
	setSolid(12, 6, true);
	
	setTile(4, 13, wall);
	setSolid(4, 13, true);
	setTile(14, 12, wall);
	setSolid(14, 12, true);

	setTile(10, 16, wall);
	setSolid(10, 16, true);*/


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
 * Sets if a tile is solid or not.
 * @param x The X grid coordinate.
 * @param y The Y grid coordinate.
 * @param solid If true the tile is solid.
 * @see isSolid()
 */
void Area::setSolid(const int x, const int y, const bool solid) {
	if(x > getWidth() || y > getHeight() || x < 0 || y < 0) {
		return;
	}

	// Already solid...
	if(isSolid(x, y) && solid) {
		return;
	}
	
	if(!solid) {
		//getPhysics()->removeRigidBody(getSolid(x, y)); done in deconstructor
		//RigidBody* delme = getSolid(x, y);
		//*(walkblockers_+(y*width_)+x) = NULL;
		//DEBUG_A("Setting not solid.");
		//delete(getSolid(x, y));
		RigidBody* blocker = *(walkblockers_+(y*width_)+x);
		if(blocker) {
			blocker->removeRigidBody_();
		}
		*(walkblockers_+(y*width_)+x) = NULL;
		//delete(delme);
	}

	/*Tile* tile = getTile(x, y);
	btRigidBody* body = NULL;
	if(isSolid) {
		float fx,fz;
		getWorldCord(x, y, fx, fz);

		btDefaultMotionState* ms = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(fx,0.5f,fz)));
		body = new btRigidBody(
			0.0f,
			ms,
			clipbox_
		);
	}
	tile->setSolid(body);*/

	if(solid) {
		//DEBUG_A("Setting solid.");
		float fx,fz;
		getWorldCord(x, y, fx, fz);
		RigidBody* blocker = new RigidBody("BLOCKER", NULL);
		//blocker->setShape(clipbox_);
		blocker->setShape(new btBoxShape(btVector3(0.5f, 0.5f, 0.5f)));
		blocker->setMass(0.0f);
		//VModel* visual = new VModel("data/models/robot-monkey.dae");
		//blocker->setVisual(*visual);
		blocker->setPos(fx, 0.5f, fz);
		//getPhysics()->getWorld()->addRigidBody();
		*(walkblockers_+(y*width_)+x) = blocker;
		addObject(*blocker);
	}
}

/**
 * Gets the RigidBody that is used to clip walking on the areas tile.
 * @param x The X grid coordinate.
 * @param y The Y grid coordinate.
 * @return The RigidBody or NULL if there is no blocker.
 */
RigidBody* Area::getSolid(const int x, const int y) {
	return *(walkblockers_+(y*width_)+x);
}

/**
 * Checks if a tile is solid or not.
 * @param x The X grid coordinate.
 * @param y The Y grid coordinate.
 * @see setSolid()
 */
bool Area::isSolid(const int x, const int y) {
	if(x > getWidth() || y > getHeight() || x < 0 || y < 0) {
		return true;
	}

	return getSolid(x, y);
}

/**
 * Renders the area and all its objects.
 * @param rm The resource manager to use to manage models and images.
 */
void Area::draw(ResourceManager& rm) {
#warning ['TODO']: Delete me....
	//glTranslatef( -TILEWIDTH * width_ / 2, 0.0f, -TILEWIDTH * height_ / 2 );
	glPushMatrix();
	for(int y = 0; y < height_; y++) {
		glPushMatrix();
		for(int x = 0; x < width_; x++) {
			Tile* tile = getTile(x, y);
			tile->draw(rm);
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
			object->draw(rm);
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
 * Gets the x, y Area grid cordinates from OpenGL world cordinates.
 * @param fx The world X cordinate to be converted.
 * @param fz The world Z (depth) cordinate to be converted.
 * @param gx The value to store the X grid cord in.
 * @param gy The value to store the Y grid cord in.
 */
void Area::getGridCord(const float fx, const float fz, int &gx, int &gy) {
	gx = -(fx-(TILEWIDTH/2))/TILEWIDTH;
	gy = -(fz-(TILEWIDTH/2))/TILEWIDTH;
}

/**
 * Gets the x, y world cordinates from Area grid world cordinates.
 * @param gx The Area grid X cordinate to be converted.
 * @param gy The Area grid Y cordinate to be converted.
 * @param fx The value to store the X world cord in.
 * @param fz The value to store the Z (depth) world cord in.
 */
void Area::getWorldCord(const int gx, const int gy, float &fx, float &fz) {
	fx = gx * TILEWIDTH;
	fz = gy * TILEWIDTH;
}
