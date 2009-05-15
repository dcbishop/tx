#ifndef TX_VISUAL_HPP
#define TX_VISUAL_HPP

#include <vector>
using namespace std;

#include "Vfx.hpp"
class Interface;

/**
 * An abstract class for visual objects that get drawn to the screen.
 * Can be used for Models, Areas, particle effect and so on.
 */
class Visual {
	public:
		Visual();

		virtual void draw(Interface* interface) {}

		void preDraw(Interface* interface);
		void postDraw(Interface* interface);

		virtual void setVisible(const bool visible);
		virtual bool isVisible();

		void addVfx(Vfx* vfx);
		void removeVfx(Vfx* vfx);
		void clearVfx();


	private:
		bool isVisible_;
		vector<Vfx*> effects_;
};

#endif /* TX_VISUAL_HPP */
