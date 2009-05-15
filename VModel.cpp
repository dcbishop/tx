#include "VModel.hpp"
#include <rcbc.h>

#include "Interface.hpp"
#include <GL/gl.h>

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
void VModel::draw(Interface* interface) {
	if(!isVisible()) {
		return;
	}

	ResourceManager* rm = interface->getResourceManager();
	if(!rm) {
		return;
	}
	Model* model = rm->loadModel(filename_);

	bool selected;
	Object* object = interface->getSelectedObject();
	if(object) {
		Visual* visual = &object->getVisual();
		selected = (this == visual);
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(1.0f, 0.2f, 0.2f);
		//DEBUG_H("Drawing selected. %s", object->getTag().c_str());
		//glEnable
	}

	if(!selected) {
		//DEBUG_H("Drawing selected. %s", object->getTag().c_str());
		glColor3f(1.0f, 1.0f, 1.0f);
		glDisable(GL_COLOR_MATERIAL);
	}
	preDraw(interface);

	RCBC_Render(model);
	postDraw(interface);
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
