#ifndef TX_FILEPROCESSOR_HPP
#define TX_FILEPROCESSOR_HPP

#include <mxml.h>

#include "Area.hpp"
#include "Object.hpp"
#include "Creature.hpp"
#include "RigidBody.hpp"

namespace FileProcessor {
	//Save Area
	void saveArea(Area& area, string filename);
	void saveArea_Objects(mxml_node_t* area_node, Area& area);
	void saveArea_Tag(mxml_node_t* node, Tagged* tagged);
	void saveArea_Object(mxml_node_t* obj_node, Object* object);
	void saveArea_Position(mxml_node_t* obj_node, Object* object);
	void saveArea_Rotation(mxml_node_t* obj_node, Object* object);
	void saveArea_Visual(mxml_node_t* obj_node, Object* object);
	void saveArea_Script(mxml_node_t* obj_node, Object* object);
	void saveArea_Tiles(mxml_node_t* area_node, Area& area);

	// Load Area
	Area* loadArea(const string filename, Area* area=NULL);
	void loadArea_Tag(mxml_node_t* node, Tagged* tagged);
	void loadArea_Area(mxml_node_t* node, Area* area);
	void loadArea_Object(mxml_node_t* node, Object* object);
	void loadArea_RigidBody(mxml_node_t* node, RigidBody* rigidbody);
	void loadArea_Creature(mxml_node_t* node, Creature* creature);
	void loadArea_Position(mxml_node_t* node, Object* object);
	void loadArea_Rotation(mxml_node_t* node, Object* object);
	void loadArea_Script(mxml_node_t* node, Object* object);
	void loadArea_Model(mxml_node_t* model_node, VModel* model);
	void loadArea_Tiles(mxml_node_t* area_node, Area* area);
}

#endif /* TX_FILEPROCESSOR_HPP */

