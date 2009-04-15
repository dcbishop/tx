#ifndef TX_RESOURCEMANAGER_HPP
#define TX_RESOURCEMANAGER_HPP

#include <map>
#include <string>
using namespace std;

#include <rcbc.h>

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
		void unloadModel(Model* model);

	private:
		List* images_;
		map< string, pair<Model*, int> > models_;
};

#endif
