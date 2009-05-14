#include "ResourceManager.hpp"
#include "console.h"

#include <ooc.h>
#include <List.h>
#include <rcbc.h>

//#include <Visual.hpp>
#include "VModel.hpp"
#include "RigidBody.hpp"

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
	//DELETE(images_);
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
		//int fullpath_size = strlen(DIRECTORY_MODELS) + strlen(filename) +1;
		//char* fullpath = malloc(fullpath_size);
		//snprintf(fullpath, fullpath_size, "%s%s", DIRECTORY_MODELS, filename);
		DEBUG_A("FLAG1 '%s', '%s'", DIRECTORY_MOD.c_str(), filename.c_str());
		string fullpath = DIRECTORY_MOD + filename;
		DEBUG_A("FLAG2");
		model = RCBC_LoadFile(fullpath.c_str(), getImages());
		DEBUG_L("Loading model '%s'", fullpath.c_str());
		pair<Model*, int> modref(model, 1);
		models_.insert(pair<string, pair<Model*, int> >(filename, modref));
		//free(fullpath);
	}

	return model;
}

/**
 * Unloads a model from use.
 * @param model The model to unload.
 */
/*void ResourceManager::unloadModel(Model* model) {
	#warning ['TODO']: Unload models...
}*/

/**
 * Decreses a refrence count for a model.
 * @param filename File of model to deref
 */
void ResourceManager::unloadModel(const string filename) {
	// Find the model in the list
	map< string, pair<Model*, int> >::iterator moditer = models_.find(filename);

	// If model isn't in list...
	if(moditer == models_.end()) {
		return;
	}

	// Decrese refrence count of model.
	pair<Model*, int> modref = moditer->second;
	modref.second--;
}

void ResourceManager::loadShapeFromModel_ProcessNode(SceneNode* node, btCompoundShape* combined) {
	DEBUG_M("Entering function...");
	Mesh* mesh = node->mesh;
	if(!mesh) {
		return;
	}

	Triangles* triangles = mesh->triangles;
	if(!triangles) {
		return;
	}

	FloatArray* vertices = triangles->vertices;
	if(!vertices) {
		return;
	}

	/*btBvhTriangleMeshShape* meshShape
	btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray();*/
	/*btTriangleMesh* triangleMesh = new btTriangleMesh();
	for(int i = 0; i < vertices->count; i+=3) {
		btVector3* vertex = new btVector3(vertices->values[i], vertices->values[i+1], vertices->values[i+2]);
		triangleMesh->addTriangle(vertex, true);
	}*/
	DEBUG_H("\tFlag...");
	// We need to make a fake index since the vertex data isn't indexed but its required by bullet
	int* triangleIndexBase = (int*)malloc(vertices->count * sizeof(int));
	for(int i = 0; i < vertices->count; i++) {
		triangleIndexBase[i] = i;
	}
	DEBUG_H("\tFlag...");
	int numTriangles = vertices->count / 3;
	int triangleIndexStride = sizeof(int) * 3;
	int vertexStride = sizeof(float) * 3;

	DEBUG_H("\tFlag...");
	btTriangleIndexVertexArray* triArray = new btTriangleIndexVertexArray(
		numTriangles,
		triangleIndexBase,
		triangleIndexStride,
		vertices->count,
		vertices->values,
		vertexStride
	);

	DEBUG_H("\tFlag...");
	// Turn triangles into a mesh...
	// Offset the mesh position...
	// Add mesh to combined object...
	float x = node->translate[0];
	float y = node->translate[1];
	float z = node->translate[2];

	DEBUG_H("\tFlag...");
	//float rx = mesh->rotations
	btQuaternion rot(0, 1, 0, 0);
	ListNode* rot_node = node->rotations->first;
	while(rot_node) {
		DEBUG_H("\t\tlooping node...");
		Rotate* rotate = (Rotate*)rot_node->data;
		if(rotate) {
			DEBUG_H("\t\t\trotate...");
			float rx = rotate->x;
			float ry = rotate->y;
			float rz = rotate->z;
			float ra = rotate->angle;
			//btQuaternion addRotation(btVector3(rx, ry, rz), ra);
			//rotation = rotation + addRotation;
			//rotation += addRotation;//btQuaternion(btVector3(rx, ry, rz), ra);
			//rotation.operator+=(addRotation);
			rot += btQuaternion(btVector3(rx, ry, rz), ra);
		}
		DEBUG_H("\tnext...");
		rot_node = rot_node->next;
	}

	DEBUG_H("\tmake mesh...");
	//btTransform* transform = new btTransform(rot, btVector3(x, y, z));
	btBvhTriangleMeshShape* trimeshShape = new btBvhTriangleMeshShape(triArray, true);
	DEBUG_H("\ttest...");
	combined->addChildShape(btTransform(rot, btVector3(x, y, z)), trimeshShape);
	//free(indices);
	#warning ['TODO']: Free indices
	DEBUG_H("\texiting function...");
}

btCollisionShape* ResourceManager::loadShapeFromModel_ProcessNodes(SceneNode* node, btCompoundShape* shape) {
	DEBUG_M("Entering function...");
	while(node) {
		loadShapeFromModel_ProcessNode(node, shape);
		if(node->child) {
			loadShapeFromModel_ProcessNodes(node->child, shape);
		}
		node = node->next;
	}
	return shape;
}

btCollisionShape* ResourceManager::loadShapeFromModel(RigidBody* body) {//Visual* visual) {
	DEBUG_M("Entering function...");
	#warning ['TODO']: Store shapes like models...
	Visual& visual = body->getVisual();
	/*if(!visual) {
		return NULL;
	}*/
	btCompoundShape* shape = new btCompoundShape();
	/*Visual& visual = getVisual();*/
	VModel* vmodel = dynamic_cast<VModel*>(&visual);
	if(!vmodel) {
		//return NULL;
		return NULL;
	}

	Model* model = loadModel(vmodel->getFilename());
	if(!model) {
		return NULL;
	}

	SceneNode* sn = model->visual_scene;
	if(!sn) {
		return NULL;
	}

	return loadShapeFromModel_ProcessNodes(sn, shape);

	/*Model* model = rm->loadModel(vmodel.getFilename()) ;
	
	btTriangleIndexVertexArray* indexVertexArrays = new
		btTriangleIndexVertexArray(model->count*/
}
