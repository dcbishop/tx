#include "Area.hpp"
#include <stdlib.h>

#warning: TODO: remove this
#include <typeinfo>
#include <GL/gl.h>


#include "console.h"


int Area::getHeight() {
	return height_;
}

int Area::getWidth() {
	return width_;
}

void Area::LoadFile(string filename) {
	DEBUG_M("Entering function...");
	height_ = 10;
	width_ = 10;
	
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
	setTile(4, 4, monkey);
	setTile(2, 7, monkey);
}

Model* Area::getTile(int x, int y) {
	//return (*(tiles_ + x) + y);
	//DEBUG_A("%s", typeid((tiles_+(y*width_)+x)));
	if(x > getWidth() || y > getHeight() || x < 0 || y < 0) {
		return NULL;
	} 
	return *(tiles_+(y*width_)+x);
}

void Area::setTile(int x, int y, Model* tile) {
	//Model** tmp = ((tiles_+(((y*width_)+x))));
	//*tmp = tile;
	//tiles_+(((y*width_)+x)) = tile;
	if(x > getWidth() || y > getHeight() || x < 0 || y < 0) {
		return;
	}
	*(tiles_+(y*width_)+x) = tile;
}

void Area::Draw() {
	glTranslatef( -TILEWIDTH * width_ / 2, 0.0f, -TILEWIDTH * height_ / 2 );
	for(int y = 0; y < height_; y++) {
		glPushMatrix();
		for(int x = 0; x < width_; x++) {
			Model* tile = getTile(x, y);
			RCBC_Render(tile);
			glTranslatef(TILEWIDTH, 0.0f, 0.0f);
		}
		glPopMatrix();
		glTranslatef(0.0f, 0.0f, TILEWIDTH);
	}
}

void Area::setResourceManager(ResourceManager* rm) {
	DEBUG_M("Entering function...");
	rm_ = rm;
}

Area::~Area() {
	DEBUG_M("Entering function...");
	delete [] tiles_;
	tiles_ = NULL;
}
