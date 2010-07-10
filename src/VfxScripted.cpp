#include "VfxScripted.hpp"

#include "Interface.hpp"
#include "GameManager.hpp"
#include "Scripting.hpp"


VfxScripted::VfxScripted(string script) {
	vfx_ = NULL;
	script_ = script;
}

VfxScripted::~VfxScripted() {
	delete(vfx_);
}

void VfxScripted::preDraw(Interface* interface) {
	int now = interface->getComputerTime();

	if(script_ != "") {
		GameManager* gm = interface->getGameManager();
		if(gm) {
			Scripting& sc = gm->getScripting();
			if(&sc) {
				luabind::globals(sc.getLuaState())["self"] = this;
				luabind::globals(sc.getLuaState())["time"] = now;
				luabind::globals(sc.getLuaState())["addr"] = (long)this;
				sc.loadLua(script_);
			}
		}
	}

	update(now);

	if(vfx_) {
		vfx_->preDraw(interface);
	}
}

void VfxScripted::postDraw(Interface* interface) {
	if(vfx_) {
		vfx_->postDraw(interface);
	}
}

Vfx* VfxScripted::getVfx() {
	return vfx_;
}

void VfxScripted::setVfx(Vfx* vfx) {
	vfx_ = vfx;
}
