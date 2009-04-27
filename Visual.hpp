#ifndef TX_VISUAL_HPP
#define TX_VISUAL_HPP

#include "ResourceManager.hpp"

/**
 * An abstract class for visual objects that get drawn to the screen.
 * Can be used for Models, Areas, particle effect and so on.
 */
class Visual {
	public:
		Visual();
		virtual void draw(ResourceManager& rm) {}
		virtual void setVisible(const bool visible);
		virtual bool isVisible();
	private:
		bool isVisible_;
};

#endif /* TX_VISUAL_HPP */
