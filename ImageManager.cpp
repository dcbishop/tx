#warning TODO: This file isnt needed...
#include "ImageManager.hpp"
#include "console.h"

ImageManager::ImageManager() {
	DEBUG_M("Entering function...");
	images_ = NEW(List);
}

ImageManager::~ImageManager() {
	DEBUG_M("Entering function...");
	#warning TODO: Free correctly
	DELETE(images_);
}
