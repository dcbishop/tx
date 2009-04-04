#include "Scripting.hpp"

#include "console.h"

Scripting::Scripting() {
	myLuaState_ = lua_open();
	
	luabind::open(myLuaState_);

	luabind::module(myLuaState_) [
		luabind::def("ScriptLog", Scripting::ScriptLog)
	];
	
	try {
		luaL_dostring(myLuaState_, "ScriptLog(\"Lua successfully initilized...\")\n");
	} catch(const std::exception &TheError) {
		errorit("LUA: %s", TheError.what());
	}
}

Scripting::~Scripting() {
	lua_close(myLuaState_);
}

void Scripting::ScriptLog(string message) {
	LOG("%s", message.c_str());
}
