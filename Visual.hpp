#ifndef TX_VISUAL_HPP
#define TX_VISUAL_HPP

#include "ResourceManager.hpp"

/**
 * An abstract class for visual objects that get drawn to the screen.
 * Can be used for Models, Areas, particle effect and so on.
 */
class Visual {
	public:
		virtual void Draw(ResourceManager& rm) {}
};

#endif
