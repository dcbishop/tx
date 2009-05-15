#ifndef TX_VFXVISUAL_HPP
#define TX_VFXVISUAL_HPP

#include "Vfx.hpp"
#include "Visual.hpp"
#include "Position.hpp"
#include "Rotation.hpp"

class VfxVisual : public Vfx, public Position, public Rotation {
	public:
		VfxVisual(Visual* visual);
		void setVisual(Visual* visual);
		void preDraw(Interface* interface);

	private:
		Visual* visual_;
};


#endif
