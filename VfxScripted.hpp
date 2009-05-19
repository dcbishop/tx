#ifndef TX_VFXSCRIPTED_HPP
#define TX_VFXSCRIPTED_HPP

#include "Vfx.hpp"
#include "Updateable.hpp"

class VfxScripted : public Vfx, public Updateable {
	public:
		VfxScripted(string script);
		~VfxScripted();
		void preDraw(Interface* interface);
		void postDraw(Interface* interface);
		Vfx* getVfx();
		void setVfx(Vfx* vfx);

	private:
		Vfx* vfx_;
		string script_;
};

#endif // TX_VFXSCRIPTED_HPP
