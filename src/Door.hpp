#warning ['TODO'] Remove this file

#if 0
#include "RigidBody.hpp"

static int DOOR_HEIGHT = 1.0f;

class Door : public RigidBody {
	public:
		void setOpen(bool isOpen);
	private:
		bool isOpen_;
		int opening_;
		int openSpeed_;
}

Door::Door() {
	isOpen_ = false;
}

void Door:setOpen(bool isOpen) {
	if(isOpen_ == isOpen) {
		return;
	} else if {
		
	}

}

bool Door::getOpen() {
	return isOpen_;
}

void Door::update(const int time) {
	Object::update(time);
}
#endif
