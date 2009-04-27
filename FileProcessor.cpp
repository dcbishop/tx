#include "FileProcessor.hpp"

#include "Creature.hpp"
#include "RigidBody.hpp"

/**
 * Used by minixml for pretty formatting of the xml output.
 * @param node 
 */
const char* whitespace_cb(mxml_node_t* node, int where) {
	const char *name = node->value.element.name;
	//DEBUG_V("%s", name);

	// Don't put any whitespace befoure <?xml> node, newline after
	if(strncmp(name, "?xml", 4) == 0) {
		if(where == MXML_WS_AFTER_OPEN) {
			return "\n";
		}
		return NULL;
	}

	if (where == MXML_WS_BEFORE_OPEN) {
	  return ("\t");
	}

	return "\n";
}

/**
 * Saves an area to an XML file.
 * @param area The area to save.
 * @param filename The name of the file to write to.
 */
void FileProcessor::saveArea(Area& area, string filename) {
	LOG("Saving area['%s'] to '%s'.", area.getTag().c_str(), filename.c_str());

	//mxml_node_t *xml = mxmlNewXML("1.0");
	mxml_node_t *xml = mxmlNewElement(NULL, "?xml version=\"1.0\" encoding=\"UTF-8\"?");

	mxml_node_t *area_node = mxmlNewElement(xml, "area");
	//mxmlElementSetAttr(area_node,"tag", area.getTag().c_str());
	saveArea_Tag(area_node, &area);
	mxmlElementSetAttrf(area_node,"width", "%d", area.getWidth());
	mxmlElementSetAttrf(area_node,"height", "%d", area.getHeight());
	saveArea_Objects(area_node, area);

	FILE *fp = fopen(filename.c_str(), "w");
	mxmlSaveFile(xml, fp, whitespace_cb);
	fclose(fp);	
}

/**
 * Dumps all objects in an area into the xml node.
 * @param area The refrence to the area.
 * @param area_node The pointer to the xml node.
 */
void FileProcessor::saveArea_Objects(mxml_node_t* area_node, Area& area) {

	for(ChildrenIterator iter = area.getFirstChild(); iter < area.getChildEnd(); iter++) {
		Tagged* tagged = dynamic_cast<Tagged*>(*iter);

		if(!tagged || tagged->isTempory()) {
			continue;
		}

		Object* object = dynamic_cast<Object*>(tagged);
		if(!object) {
			return;
		}

		Creature* creature = dynamic_cast<Creature*>(tagged);
		RigidBody* rigid_body = dynamic_cast<RigidBody*>(tagged);

		DEBUG_A("XML PROCESSING CHILD: '%s'", tagged->getTag().c_str());

		mxml_node_t *obj_node;
		if(creature) {
			obj_node = mxmlNewElement(area_node, "creature");
		} else if (rigid_body) {
			obj_node = mxmlNewElement(area_node, "rigidbody");
		} else {
			obj_node = mxmlNewElement(area_node, "object");
		}
		saveArea_Object(obj_node, object);
	}
	//area.getFirstChild();
}

/**
 * Sets the objects tag in the XML node.
 * @param node The XML node.
 * @param tagged The tagged object.
 */
void FileProcessor::saveArea_Tag(mxml_node_t* node, Tagged* tagged) {
	mxmlElementSetAttrf(node, "tag", "%s", tagged->getTag().c_str());
}

/**
 * Dumps an Object into the xml node.
 * @param object The refrence to the object.
 * @param obj_node The pointer to the xml node.
 */
void FileProcessor::saveArea_Object(mxml_node_t* obj_node, Object* object) {
	saveArea_Tag(obj_node, object);
	saveArea_Position(obj_node, object);
	saveArea_Rotation(obj_node, object);
	saveArea_Visual(obj_node, object);
	saveArea_Script(obj_node, object);
}

/**
 * Dumps an Objects position into the xml node.
 * @param object The object.
 * @param obj_node The XML node.
 */
void FileProcessor::saveArea_Position(mxml_node_t* obj_node, Object* object) {
	mxml_node_t *pos_node = mxmlNewElement(obj_node, "position");
	mxmlElementSetAttrf(pos_node, "x", "%f", object->getX());
	mxmlElementSetAttrf(pos_node, "y", "%f", object->getY());
	mxmlElementSetAttrf(pos_node, "z", "%f", object->getZ());
}

/**
 * Dumps an Objects rotation into the xml node.
 * @param obj_node The XML node.
 * @param object The Object.
 */
void FileProcessor::saveArea_Rotation(mxml_node_t* obj_node, Object* object) {
	mxml_node_t *rot_node = mxmlNewElement(obj_node, "rotation");
	mxmlElementSetAttrf(rot_node, "rx", "%f", object->getRotX());
	mxmlElementSetAttrf(rot_node, "ry", "%f", object->getRotY());
	mxmlElementSetAttrf(rot_node, "rz", "%f", object->getRotZ());
	mxmlElementSetAttrf(rot_node, "angle", "%f", object->getRotAngle());
}

/**
 * Dumps an Object Visual information into the xml node.
 * @param obj_node The XML node.
 * @param object The Object.
 */
void FileProcessor::saveArea_Visual(mxml_node_t* obj_node, Object* object) {
	Visual* visual = &object->getVisual();
	VModel* vmodel = dynamic_cast<VModel*>(visual);

	if(!vmodel) {
		return;
	}

	mxml_node_t *mod_node = mxmlNewElement(obj_node, "model");
	mxmlElementSetAttrf(mod_node, "filename", "%s", vmodel->getFilename().c_str());

	string visiblity = "true";
	if(!vmodel->isVisible()) {
		visiblity = "false";
	}

	mxmlElementSetAttrf(mod_node, "visible", "%s", visiblity.c_str());
}


/**
 * Dumps an Objects scripts into the XML node.
 * @param obj_node XML node.
 * @param object The object.
 */
void FileProcessor::saveArea_Script(mxml_node_t* obj_node, Object* object) {
	mxml_node_t *pos_node = mxmlNewElement(obj_node, "script");
	mxmlElementSetAttrf(pos_node, "type", "onupate");
	mxmlElementSetAttrf(pos_node, "filename", object->getScript(SCRIPT_ONUPDATE).c_str());
}
