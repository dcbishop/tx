#include "VModel.hpp"
#include <rcbc.h>

/*VModel::VModel() {
	filename_ = "";
}*/

/**
 * @param filename The filename of the COLLADA model to load.
 */
VModel::VModel(const string filename) {
	setFilename(filename);
}

/**
 * Retrieves the model data from the resource manager and rraws the
 * Model to screen using RCBC.
 * @param rm The ResourceManager to use to load the model
 */
void VModel::draw(ResourceManager& rm) {
	Model* model = rm.loadModel(filename_);
	RCBC_Render(model);
}

/**
 * Returns the filename.
 * @return The filename of the model.
 */
string VModel::getFilename() {
	return filename_;
}

/**
 * Sets the filename of the model.
 * @param filename The filename of the model.
 */
void VModel::setFilename(string filename) {
#warning ['TODO']: Maybe unload model (also add deconstructor)...
	filename_ = filename;
}
