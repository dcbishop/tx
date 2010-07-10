#ifndef TX_VFX_HPP
#define TX_VFX_HPP

class Interface;
#include "Container.hpp"

/** 
 * An abstract class for applying visual effects to objects.
 */
class Vfx : public Contained {
	public:
		/** Code to run befoure rendering the object */
		virtual void preDraw(Interface* interface){};

		/** Code to run after rendering the object */
		virtual void postDraw(Interface* interface){};
};

#endif /* TX_VFX_HPP */
