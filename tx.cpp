#include <iostream>
#include <string>

using namespace std;
using std::string;

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
#include <iostream>
#include <luabind/luabind.hpp>

#include <btBulletDynamicsCommon.h>

#include <rcbc.h>

#include "Area.hpp"
#include "Interface.hpp"
#include "ResourceManager.hpp"
#include "console.h"

void lua_log(string message) {
	LOG("%s", message.c_str());
}

int main(int argc, char* argv[]) {
	LOG("TX starting...");
	
	lua_State *myLuaState = lua_open();
	luabind::open(myLuaState);
	luabind::module(myLuaState) [
		luabind::def("lua_log", lua_log)
	];
	
	try {
		luaL_dostring(myLuaState, "lua_log(\"Lua successfully initilized...\")\n");
	} catch(const std::exception &TheError) {
		errorit("LUA: %s", TheError.what());
	}
	

	
	int maxProxies = 1024; /* Maximum number of rigid bodies */
#warning ['TODO']: This should be the size of the world.
	btVector3 worldAabbMin(-10000,-10000,-10000);
	btVector3 worldAabbMax(10000,10000,10000);
	btAxisSweep3* broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax,maxProxies);
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	
	ResourceManager rm;

	Area area;
	area.setResourceManager(&rm);

	Interface interface(800, 600);
	RCBC_Init();

	Creature player;
	Model* playermod = RCBC_LoadFile("data/models/monkey-robot.dae", rm.getImages());
	player.setModel(playermod);

	Model* textobjmod = RCBC_LoadFile("data/models/unmaptest.dae", rm.getImages());
	Object testobj;
	testobj.setModel(textobjmod);

	area.LoadFile("data/areas/test-area.xml");
	area.addObject(&player);
	area.addObject(&testobj);
	interface.setCreature(&player);
	interface.setArea(&area);
	interface.MainLoop();
	
	DELETE(playermod);
	DELETE(textobjmod);
	lua_close(myLuaState);
	LOG("TX finished...");
	return 0;
}
