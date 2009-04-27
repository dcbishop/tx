#ifndef TX_FILEPROCESSOR_HPP
#define TX_FILEPROCESSOR_HPP

#include <mxml.h>

#include "Area.hpp"

namespace FileProcessor {
	void saveArea(Area& area, string filename);
	void saveArea_Objects(mxml_node_t* area_node, Area& area);
	void saveArea_Tag(mxml_node_t* node, Tagged* tagged);
	void saveArea_Object(mxml_node_t* obj_node, Object* object);
	void saveArea_Position(mxml_node_t* obj_node, Object* object);
	void saveArea_Rotation(mxml_node_t* obj_node, Object* object);
	void saveArea_Visual(mxml_node_t* obj_node, Object* object);
	void saveArea_Script(mxml_node_t* obj_node, Object* object);

}

#endif /* TX_FILEPROCESSOR_HPP */

