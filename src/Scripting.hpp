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
#include <luabind/class_info.hpp> 

/**
 * A class controlling the LUA script virtual machine.
 */
class Scripting {
	public:
		Scripting();
		~Scripting();
		void loadLua(const string filename);
		void doString(const string str);
		lua_State* getLuaState();

	private:
		static void ScriptLog_(string msg);
		//static long getMemoryAddress_(void* ptr);

		
		void bindAll_();
		luabind::scope bindBullet_();
		luabind::scope bindGameManager_();
		luabind::scope bindTagged_();
		luabind::scope bindContainer_();
		luabind::scope bindContained_();
		luabind::scope bindUpdateable_();
		luabind::scope bindPosition_();
		luabind::scope bindRotation_();
		luabind::scope bindLocation_();
		luabind::scope bindVisual_();
		luabind::scope bindVModel_();
		luabind::scope bindTile_();
		luabind::scope bindVfx_();
		luabind::scope bindVfxColour_();
		luabind::scope bindVfxScripted_();
		luabind::scope bindObject_();
		luabind::scope bindLight_();
		luabind::scope bindRigidBody_();
		luabind::scope bindCreature_();
		luabind::scope bindArea_();
		luabind::scope bindColour_();

		lua_State *myLuaState_;
};

#endif /* TX_SCRIPTING_HPP */
