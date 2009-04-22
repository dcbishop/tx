#if 0
#warning ['TODO']: This file isnt needed...
#include "ImageManager.hpp"
#include "console.h"

ImageManager::ImageManager() {
	DEBUG_M("Entering function...");
	images_ = NEW(List);
}

ImageManager::~ImageManager() {
	DEBUG_M("Entering function...");
	#warning TODO: Free correctly
	List_Delete(images_);
	DELETE(images_);
}

#endif
