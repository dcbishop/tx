#include "Scripting.hpp"

#include "console.h"
#include "Object.hpp"
#include "RigidBody.hpp"
#include "GameManager.hpp"

Scripting::Scripting() {
	myLuaState_ = lua_open();
	if(!myLuaState_) {
		//ERROR("Failed to init Lua...");
		throw "LUAFAILED";
	}

	luaL_openlibs(myLuaState_);

	luabind::open(myLuaState_);
	luabind::module(myLuaState_) [
		luabind::def("ScriptLog", Scripting::ScriptLog_),
		luabind::def("address", Scripting::ScriptAddress_)
	];

	bindAll_();

	try {
		luaL_dostring(myLuaState_, "ScriptLog(\"Lua successfully initilized...\")\n");
		luaL_dostring(myLuaState_, "globals = {}\n");
	} catch(const std::exception &TheError) {
		//ERROR("LUA: %s", TheError.what());
	}
}

Scripting::~Scripting() {
	lua_close(myLuaState_);
}

/**
 * Executes a lua script from a file.
 * @param filename The name of the file to execute.
 */
void Scripting::loadLua(const string filename) {
	int result = luaL_dofile(myLuaState_, filename.c_str());
	if(result) {
		//ERROR("LUA error loading '%s'", filename);
		luaL_dostring(myLuaState_, "ScriptLog(\"Error loading script.\")\n");
	}
}

/**
 * Retusn the Lua virtual machine.
 * @return The Lua state.
 */
lua_State* Scripting::getLuaState() {
	return myLuaState_;
}

/**
 * Executes a lua command on the lua state.
 * @param str The string to execute.
 */
void Scripting::doString(const string str) {
	luaL_dostring(myLuaState_, str.c_str());
}

void Scripting::ScriptLog_(string message) {
	LOG("%s", message.c_str());
}

long Scripting::ScriptAddress_(void *ptr) {
	return (long)ptr;
}

void Scripting::bindAll_() {
	luabind::module(myLuaState_) [
		bindUpdateable_(),
		bindContainer_(),
		bindGameManager_(),
		bindTagged_(),
		bindVisual_(),
		bindObject_(),
		bindRigidBody_(),
		bindArea_()
	];
}

luabind::scope Scripting::bindUpdateable_() {
	return luabind::class_<Updateable>("Updateable")
		//.def(luabind::constructor<>())
		//.def("update", &Updateable::update)
		.property("last_update", &Updateable::getLastupdate)
	;
}

luabind::scope Scripting::bindContainer_() {
	return luabind::class_<Container>("Container")
		.def("getAreaByTag", &Container::getAreaByTag)
		.def("getObjectByTag", &Container::getObjectByTag)
		.def("getCreatureByTag", &Container::getCreatureByTag)
	;
}

luabind::scope Scripting::bindTagged_() {
	return luabind::class_<Tagged>("Tagged")
		//.def(luabind::constructor<>())
		.property("tag", &Tagged::getTag, &Tagged::setTag)
		.property("gm", &Tagged::getGameManager, &Tagged::setGameManager)
		.property("isTempory", &Tagged::isTempory, &Tagged::setTempory)
	;
}
	
luabind::scope Scripting::bindVisual_() {
	return luabind::class_<Visual>("Visual")
		.property("isVisible", &Visual::isVisible, &Visual::setVisible)
	;
}

luabind::scope Scripting::bindGameManager_() {
	return
		luabind::class_<GameManager, luabind::bases<Updateable, Container> >("GameManager")
			//.def(luabind::constructor<>())
		;
}

luabind::scope Scripting::bindObject_() {
	return
		luabind::class_<Object, luabind::bases<Updateable, Tagged, Visual> >("Object")
			.def(luabind::constructor<>())
			.property("area", &Object::getArea, &Object::setArea)
			.property("x", &Object::getX, &Object::setX)
			.property("y", &Object::getY, &Object::setY)
			.property("z", &Object::getZ, &Object::setZ)
			.property("rx", &Object::getRotX, &Object::setRotX)
			.property("ry", &Object::getRotY, &Object::setRotY)
			.property("rz", &Object::getRotZ, &Object::setRotZ)
			.property("angle", &Object::getRotAngle, &Object::setRotAngle)
			.def("setScript", &Object::setScript)
			.def("getScript", &Object::getScript)
			.def("setPos", &Object::setPos)
		;
}

luabind::scope Scripting::bindRigidBody_() {
	return
		luabind::class_<RigidBody, luabind::bases<Object, Tagged> >("RigidBody")
			.def(luabind::constructor<>())
			/*.property("area", &RigidBody::getArea, &RigidBody::setArea)
			.property("x", &RigidBody::getX, &RigidBody::setX)
			.property("y", &RigidBody::getY, &RigidBody::setY)
			.property("z", &RigidBody::getZ, &RigidBody::setZ)
			.property("rx", &RigidBody::getRotX, &RigidBody::setRotX)
			.property("ry", &RigidBody::getRotY, &RigidBody::setRotY)
			.property("rz", &RigidBody::getRotZ, &RigidBody::setRotZ)
			.property("angle", &RigidBody::getRotAngle, &RigidBody::setRotAngle)*/
	;

}

luabind::scope Scripting::bindArea_() {
	return
		luabind::class_<Area, luabind::bases<Tagged, Updateable, Container> >("Area")
			.def(luabind::constructor<>())
			.property("width", &Area::getWidth, &Area::setWidth)
			.property("height", &Area::getHeight, &Area::setHeight)
			.def("setSize", &Area::setSize)
			.def("loadFile", &Area::loadFile)
			.def("fill", &Area::fill)
			.def("boxRoom", &Area::boxRoom)
			.def("addObject", &Area::addObject)
			.def("removeObject", &Area::removeObject)
			.def("setSolid", &Area::setSolid)
			.def("isSolid", &Area::isSolid)
			.def("getGridCord", &Area::getGridCord)
			.def("getWorldCord", &Area::getWorldCord)
	;
}
