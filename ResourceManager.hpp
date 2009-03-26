#ifndef TX_RESOURCEMANAGER_HPP
#define TX_RESOURCEMANAGER_HPP

#include <rcbc.h>

class ResourceManager {
	public:
		ResourceManager();
		~ResourceManager();
		List* getImages();
		List* getTextures();
	private:
		List* images_;
		List* models_;
};

#endif
