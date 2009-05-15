#ifndef TX_VFXCOLOUR_HPP
#define TX_VFXCOLOUR_HPP

#include "Vfx.hpp"

class VfxColour : public Vfx {
	public:
		VfxColour(float red, float green, float blue, float alpha = 1.0f);
		void preDraw(Interface* interface);
		void postDraw(Interface* interface);
		void setColour(float red, float green, float blue, float alpha = 1.0f);

	private:
		float red_;
		float green_;
		float blue_;
		float alpha_;
};

#endif /* TX_VFXCOLOUR_HPP */
