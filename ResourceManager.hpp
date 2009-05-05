#ifndef TX_RESOURCEMANAGER_HPP
#define TX_RESOURCEMANAGER_HPP

#include <map>
#include <string>
using namespace std;

#include <rcbc.h>

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

	private:
		List* images_;
		map< string, pair<Model*, int> > models_;
};

#endif /* TX_RESOURCEMANAGER_HPP */
