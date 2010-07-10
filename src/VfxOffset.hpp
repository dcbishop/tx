#ifndef TX_VFXOFFSET_HPP
#define TX_VFXOFFSET_HPP

#include "Vfx.hpp"
#include "Position.hpp"

/**
 * Renders the object at a different offset.
 */
class VfxOffset : public Vfx, public Position {
	public:
		VfxOffset(float x, float y, float z);
		void preDraw(Interface* interface);
		void postDraw(Interface* interface);
};

#endif /* TX_VFXOFFSET_HPP */
