#include "ResourceManager.hpp"
#include "console.h"

ResourceManager::ResourceManager() {
	DEBUG_M("Entering function...");
	images_ = NEW(List);
	models_ = NEW(List);
}

ResourceManager::~ResourceManager() {
	DEBUG_M("Entering function...");

	#warning: ['TODO']: Free correctly...
	//List_DeleteData(images_);
	//List_DeleteData(models_);
	DELETE(images_);
	DELETE(models_);
}

/**
 * @return Pointer to a RCBC List containing all the Images.
 */
List* ResourceManager::getImages() {
	DEBUG_M("Entering function...");
	return images_;
}
/**
 * @return Pointer to a RCBC List containing all the Models.
 */
List* ResourceManager::getModels() {
	DEBUG_M("Entering function...");
	return models_;
}
