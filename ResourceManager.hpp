#ifndef TX_RESOURCEMANAGER_HPP
#define TX_RESOURCEMANAGER_HPP

#include <map>
#include <string>
using namespace std;

#include <rcbc.h>

//#include "Visual.hpp"
class Visual;
class RigidBody;
#include <btBulletDynamicsCommon.h>


static string DIRECTORY_MOD = "data/models/";
static string DIRECTORY_SCRIPTS = "data/scripts/";

/**
 * Contains a list of game resources that are in memory such as textures.
 */
class ResourceManager {
	public:
		ResourceManager();
		~ResourceManager();
		virtual List* getImages();
		//virtual List* getModels();
		virtual Model* loadModel(const string filename);
		//void unloadModel(Model* model);
		void unloadModel(const string model);
		/*btCollisionShape* loadShapeFromModel(RigidBody* body);
		btCollisionShape* loadShapeFromModel_ProcessNodes(SceneNode* node, btCompoundShape* shape);
		void loadShapeFromModel_ProcessNode(SceneNode* node, btCompoundShape* combined);
		btCollisionShape* loadShapeBox(const float x, const float y, const float z);*/


	private:
		List* images_;
		map< string, pair<Model*, int> > models_;
};

#endif /* TX_RESOURCEMANAGER_HPP */
