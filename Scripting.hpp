#ifndef TX_SCRIPTING_HPP
#define TX_SCRIPTING_HPP

#include <string>
using namespace std;

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <luabind/luabind.hpp>

/**
 * A class controlling the LUA script virtual machine.
 */
class Scripting {
	public:
		Scripting();
		~Scripting();
		void loadLua(const string filename);
		lua_State* getLuaState();

	private:
		static void ScriptLog_(string msg);
		static long ScriptAddress_(void *ptr);
		
		void bindAll_();
		luabind::scope bindGameManager_();
		luabind::scope bindTagged_();
		luabind::scope bindUpdateable_();
		luabind::scope bindObject_();
		luabind::scope bindRigidBody_();
		luabind::scope bindArea_();


		lua_State *myLuaState_;
};

#endif
