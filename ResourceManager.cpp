#include "ResourceManager.hpp"
#include "console.h"

ResourceManager::ResourceManager() {
	DEBUG_M("Entering function...");
	images_ = NEW(List);
	models_ = NEW(List);
}

ResourceManager::~ResourceManager() {
	DEBUG_M("Entering function...");

	#warning: TODO: Free correctly...
	//List_DeleteData(images_);
	//List_DeleteData(models_);
	DELETE(images_);
	DELETE(models_);
}

List* ResourceManager::getImages() {
	DEBUG_M("Entering function...");
	return images_;
}

List* ResourceManager::getTextures() {
	DEBUG_M("Entering function...");
	return models_;
}
