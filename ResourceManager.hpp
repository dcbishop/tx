#ifndef TX_RESOURCEMANAGER_HPP
#define TX_RESOURCEMANAGER_HPP

#include <rcbc.h>

/**
 * Contains a list of game resources that are in memory such as textures.
 */
class ResourceManager {
	public:
		ResourceManager();
		~ResourceManager();
		virtual List* getImages();
		virtual List* getModels();
	private:
		List* images_;
		List* models_;
};

#endif
