#include "Scripting.hpp"

#include "console.h"

#include "Object.hpp"

Scripting::Scripting() {
	myLuaState_ = lua_open();
	
	luabind::open(myLuaState_);

	luabind::module(myLuaState_) [
		luabind::def("ScriptLog", Scripting::ScriptLog_)
	];
	
	bindAll_();
	
	try {
		luaL_dostring(myLuaState_, "ScriptLog(\"Lua successfully initilized...\")\n");
	} catch(const std::exception &TheError) {
		errorit("LUA: %s", TheError.what());
	}
	
	
}

Scripting::~Scripting() {
	lua_close(myLuaState_);
}

void Scripting::ScriptLog_(string message) {
	LOG("%s", message.c_str());
}

void Scripting::bindAll_() {
	luabind::module(myLuaState_) [
		bindObject_()
	];
}

luabind::scope Scripting::bindObject_() {
	return
		luabind::class_<Object>("Object")
			.def(luabind::constructor<>())
			.property("area", &Object::getArea, &Object::setArea)
			.property("x", &Object::getX, &Object::setX)
			.property("y", &Object::getY, &Object::setY)
			.property("z", &Object::getZ, &Object::setZ)
			.property("rx", &Object::getRotX, &Object::setRotX)
			.property("ry", &Object::getRotY, &Object::setRotY)
			.property("rz", &Object::getRotZ, &Object::setRotZ)
			.property("angle", &Object::getRotAngle, &Object::setRotAngle)
		;
}