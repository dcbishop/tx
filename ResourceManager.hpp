#ifndef TX_RESOURCEMANAGER_HPP
#define TX_RESOURCEMANAGER_HPP

#include <rcbc.h>

class ResourceManager {
	public:
		ResourceManager();
		~ResourceManager();
		virtual List* getImages();
		virtual List* getTextures();
	private:
		List* images_;
		List* models_;
};

#endif
