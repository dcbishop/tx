#include "VModel.hpp"
#include <rcbc.h>

VModel::VModel() {
	filename_ = "";
	//model_ = NULL;
}

/**
 * @param filename The filename of the COLLADA model to load.
 */
VModel::VModel(const string filename) {
	filename_ = filename;
	//model_ = NULL;
}

/**
 * Retrieves the model data from the resource manager and rraws the
 * Model to screen using RCBC.
 * @param rm The ResourceManager to use to load the model
 */
void VModel::draw(ResourceManager& rm) {
	/*if(!model_); {
		model_ = rm.loadModel(filename_);
	}*/
	Model* model = rm.loadModel(filename_);
	RCBC_Render(model);
	//rm.unloadModel(filename_);
	//RCBC_Render(model_);
}
