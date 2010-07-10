#include "FileProcessor.hpp"

#include "Tile.hpp"
#include "GameManager.hpp"

/**
 * Used by minixml for pretty formatting of the xml output.
 * @param node 
 * @param where 
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

	// First depth level
	if(!strcmp(name, "area")) {
		if(where == MXML_WS_BEFORE_OPEN) {
			return "";
		}
	}

	// Second depth level
	if(!strcmp(name, "object") ||
			!strcmp(name, "rigidbody") ||
			!strcmp(name, "creature") ||
			!strcmp(name, "tiles")) {
		if(where == MXML_WS_BEFORE_OPEN) {
			return "\t";
		}
	}

	// Third depth level
	if(!strcmp(name, "position") ||
			!strcmp(name, "rotation") ||
			!strcmp(name, "script") ||
			!strcmp(name, "model") ||
			!strcmp(name, "tile")) {
		if(where == MXML_WS_BEFORE_OPEN) {
			return "\t\t";
		}
	}

	if (where == MXML_WS_BEFORE_OPEN || where == MXML_WS_BEFORE_CLOSE) {
	  return ("\t");
	}

	if(where == MXML_WS_AFTER_OPEN) {
		return "\n";
	}
	if(where == MXML_WS_AFTER_CLOSE) {
			return "\n";
	}

	return "";
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
	saveArea_Tag(area_node, &area);
	mxmlElementSetAttrf(area_node,"width", "%d", area.getWidth());
	mxmlElementSetAttrf(area_node,"height", "%d", area.getHeight());
	saveArea_Objects(area_node, area);
	saveArea_Tiles(area_node, area);

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

	for(ChildrenIterator iter = area.getChildBegin(); iter < area.getChildEnd(); iter++) {
		Tagged* tagged = dynamic_cast<Tagged*>(*iter);

		if(!tagged || tagged->isTempory()) {
			continue;
		}

		Object* object = dynamic_cast<Object*>(tagged);
		if(!object) {
			continue;
		}

		Creature* creature = dynamic_cast<Creature*>(tagged);
		RigidBody* rigid_body = dynamic_cast<RigidBody*>(tagged);

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
	if(object->isVisible()) {
		mxmlElementSetAttr(obj_node, "visible", "true");
	} else {
		mxmlElementSetAttr(obj_node, "visible", "false");
	}
	#warning ['TODO']: Fix me!
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
	if(!visual) {
		return;
	}

	VModel* vmodel = dynamic_cast<VModel*>(visual);

	if(!vmodel) {
		return;
	}

	const char* filename = vmodel->getFilename().c_str();
	mxml_node_t *mod_node = mxmlNewElement(obj_node, "model");
	mxmlElementSetAttrf(mod_node, "filename", "%s", filename);

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
	if(strcmp(object->getScript(SCRIPT_ONUPDATE).c_str(), "") != 0) {
		mxml_node_t *pos_node = mxmlNewElement(obj_node, "script");
		mxmlElementSetAttr(pos_node, "type", "onupdate");
		mxmlElementSetAttr(pos_node, "filename", object->getScript(SCRIPT_ONUPDATE).c_str());
	}
}

/**
 * Dumps all tile in an area into the xml node.
 * @param area The refrence to the area.
 * @param area_node The pointer to the xml node.
 */
void FileProcessor::saveArea_Tiles(mxml_node_t* area_node, Area& area) {
	mxml_node_t *tiles_node = mxmlNewElement(area_node, "tiles");
	for(int y = 0; y < area.getHeight(); y++) {
		for(int x = 0; x < area.getWidth(); x++) {

			Tile* tile = area.getTile(x, y);
			if(!tile) {
				continue;
			}

			mxml_node_t *tile_node = mxmlNewElement(tiles_node, "tile");
			mxmlElementSetAttrf(tile_node, "x", "%d", x);
			mxmlElementSetAttrf(tile_node, "y", "%d", y);

			const char* solid = "false";
			if(area.getSolid(x, y)) {
				solid = "true";
			}
			mxmlElementSetAttr(tile_node, "solid", solid);

			const char* filename = tile->getFilename().c_str();
			mxmlElementSetAttr(tile_node, "filename", filename);

			mxmlElementSetAttrf(tile_node, "rotation", "%f", tile->getRotation());
		}
	}
}

/**
 * Loads an area from XML file.
 * @param filename of the Area to load.
 * @param area An optional pointer to the area to load this into, otherwise a new one will be made.
 * @return Pointer to the loaded Area.
 */
Area* FileProcessor::loadArea(const string filename, Area* area) {
	if(!area) {
		area = new Area(DEFAULT_TAG);
	}

	FILE* fp;
	mxml_node_t *tree, *node;
	fp = fopen(filename.c_str(), "r");
	if(!fp) {
		return NULL;
	}

	tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);
	fclose(fp);

	for(node = tree->child; node; node = node->next) {
		if(node->type == MXML_ELEMENT) {
			if(strcasecmp(node->value.element.name, "area") == 0) {
				loadArea_Area(node, area);
			}
		}
	}

	mxmlDelete(tree);
	return area;
}

/**
 * Loads a tag from the XML node to the Object.
 * @param node The XML node with a "tag" attribute (<area>, <object>, <rigidbody> or <creature>).
 * @param tagged The Object to be tagged.
 */
void FileProcessor::loadArea_Tag(mxml_node_t* node, Tagged* tagged) {
	tagged->setTag(mxmlElementGetAttr(node, "tag"));
}

/**
 * Loads the Object from XML file.
 * @param obj_node The <object> node.
 * @param object The Object.
 */
void FileProcessor::loadArea_Object(mxml_node_t* obj_node, Object* object) {
	loadArea_Tag(obj_node, object);

	const char* visibility_s = mxmlElementGetAttr(obj_node, "visible");
	if(visibility_s != NULL && strncasecmp(visibility_s, "false", strlen(visibility_s)) == 0) {
		object->setVisible(false);
	} else {
		object->setVisible(true);
	}

	mxml_node_t* node;
	for(node = obj_node->child; node; node = node->next) {
		if(node->type == MXML_ELEMENT) {
			if(strcasecmp(node->value.element.name, "position") == 0) {
				loadArea_Position(node, object);
			} else if(strcasecmp(node->value.element.name, "rotation") == 0) {
				loadArea_Rotation(node, object);
			} else if(strcasecmp(node->value.element.name, "script") == 0) {
				loadArea_Script(node, object);
			} else if(strcasecmp(node->value.element.name, "model") == 0) {
				VModel* model = new VModel();
				model->setVisible(object->isVisible());
				loadArea_Model(node, model);
				object->setVisual(model);
			}
		}
	}
}

/**
 * Loads the RigidBody from XML.
 * @param node <rigidbody> node.
 * @param rigidbody The RigidBody.
 */
void FileProcessor::loadArea_RigidBody(mxml_node_t* node, RigidBody* rigidbody) {
	loadArea_Object(node, rigidbody);
}

/**
 * Loads the Creature from an XML node.
 * @param node The <creature> node.
 * @param creature The Creature.
 */
void FileProcessor::loadArea_Creature(mxml_node_t* node, Creature* creature) {
	loadArea_RigidBody(node, creature);
}

/**
 * Loads an area from an XML node.
 * @param node The <area> node.
 * @param area The Area.
 */
void FileProcessor::loadArea_Area(mxml_node_t* area_node, Area* area) {
	loadArea_Tag(area_node, area);

	const char* sWidth = mxmlElementGetAttr(area_node, "width");
	const char* sHeight = mxmlElementGetAttr(area_node, "height");

	area->setSize(atoi(sWidth), atoi(sHeight));

	mxml_node_t* node;
	for(node = area_node->child; node; node = node->next) {
		if(node->type == MXML_ELEMENT) {
			Object* object = NULL;
			if(strcasecmp(node->value.element.name, "object") == 0) {
				object = new Object();
				loadArea_Object(node, object);
			} else if(strcasecmp(node->value.element.name, "rigidbody") == 0) {
				RigidBody* rigidbody = new RigidBody();
				loadArea_RigidBody(node, rigidbody);
				object = rigidbody;
			} else if(strcasecmp(node->value.element.name, "creature") == 0) {
				Creature* creature = new Creature();
				loadArea_RigidBody(node, creature);
				object = creature;
			} else if(strcasecmp(node->value.element.name, "tiles") == 0) {
				loadArea_Tiles(node, area);
			}

			if(object) {
				area->addObject(object);
				//GameManager* gm = area->getGameManager();
				//gm->registerObject(object);
			}
		}
	}
}

/**
 * Loads the potition on an Object from XML node.
 * @param node The <position> node.
 * @param object The Object.
 */
void FileProcessor::loadArea_Position(mxml_node_t* node, Object* object) {
	const char* sX = mxmlElementGetAttr(node, "x");
	const char* sY = mxmlElementGetAttr(node, "y");
	const char* sZ = mxmlElementGetAttr(node, "z");
	object->setXYZ(atof(sX), atof(sY), atof(sZ));
}

/**
 * Loads the rotation on an Object from XML node.
 * @param node The <rotation> node.
 * @param object The Object.
 */
void FileProcessor::loadArea_Rotation(mxml_node_t* node, Object* object) {
	const char* sRX = mxmlElementGetAttr(node, "rx");
	const char* sRY = mxmlElementGetAttr(node, "ry");
	const char* sRZ = mxmlElementGetAttr(node, "rz");
	const char* sAngle = mxmlElementGetAttr(node, "angle");

	object->setRotX(atof(sRX));
	object->setRotY(atof(sRY));
	object->setRotZ(atof(sRZ));
	object->setRotAngle(atof(sAngle));
}

/**
 * Loads scripts into an Object.
 * @param node The <script> node.
 * @param object The Object.
 */
void FileProcessor::loadArea_Script(mxml_node_t* node, Object* object) {
	const char* stype = mxmlElementGetAttr(node, "type");
	const char* filename = mxmlElementGetAttr(node, "filename");

	int script_type = SCRIPT_ONUPDATE;
	if(strcasecmp(stype, "onupdate") == 0) {
		object->setScript(script_type, filename);
	}
}

/**
 * Loads model information into a Model.
 * @param model_node The <mode> node.
 * @param model The VModel
 */
void FileProcessor::loadArea_Model(mxml_node_t* model_node, VModel* model) {
	const char* filename = mxmlElementGetAttr(model_node, "filename");
	model->setFilename(filename);

	const char* vstr = mxmlElementGetAttr(model_node, "visible");
	if(strcasecmp(vstr, "false") == 0) {
		model->setVisible(false);
	} else {
		model->setVisible(true);
	}
}

/**
 * 
 */
void FileProcessor::loadArea_Tiles(mxml_node_t* tiles_node, Area* area) {
	mxml_node_t* node;
	for(node = tiles_node->child; node; node = node->next) {
		if(node->type == MXML_ELEMENT) {
			if(strcasecmp(node->value.element.name, "tile") == 0) {
				const char* sX = mxmlElementGetAttr(node, "x");
				const char* sY = mxmlElementGetAttr(node, "y");
				const char* sSolid = mxmlElementGetAttr(node, "solid");
				const char* sFilename = mxmlElementGetAttr(node, "filename");
				const char* sRotation = mxmlElementGetAttr(node, "rotation");

				int x = atoi(sX);
				int y = atoi(sY);
				float rotation = atof(sRotation);

				Tile* tile = new Tile(sFilename);
				tile->setRotation(rotation);
				area->setTile(x, y, tile);

				if(!strcasecmp(sSolid, "true")) {
					area->setSolid(x, y, true);
				} else {
					area->setSolid(x, y, false);
				}
			}
		}
	}
}
