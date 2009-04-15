#include "ResourceManager.hpp"
#include "console.h"

ResourceManager::ResourceManager() {
	DEBUG_M("Entering function...");
	images_ = NEW(List);
	//models_ = NEW(List);
}

ResourceManager::~ResourceManager() {
	DEBUG_M("Entering function...");

	#warning: ['TODO']: Free correctly...
	//List_DeleteData(images_);
	//List_DeleteData(models_);
	DELETE(images_);
	//DELETE(models_);
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
/*List* ResourceManager::getModels() {
	DEBUG_M("Entering function...");
	return models_;
}*/

/**
 * Loads a model from a file if needed or increases its refrence count.
 * @return Pointer to the loaded model.
 */
Model* ResourceManager::loadModel(const string filename) {
	map< string, pair<Model*, int> >::iterator moditer = models_.find(filename);
	Model* model = NULL;
	if(moditer != models_.end()) {
		pair<Model*, int> modref = moditer->second;
		model = modref.first;
		modref.second++;
	} else {
		model = RCBC_LoadFile(filename.c_str(), getImages());
		pair<Model*, int> modref(model, 1);
		models_.insert(pair<string, pair<Model*, int> >(filename, modref));
	}

	return model;
}

/**
 * Unloads a model from use.
 */
void ResourceManager::unloadModel(Model* model) {
	#warning ['TODO']: Unload models...
}
