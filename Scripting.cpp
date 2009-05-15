#include "Scripting.hpp"

#include "console.h"
#include "Location.hpp"
#include "Position.hpp"
#include "Object.hpp"
#include "RigidBody.hpp"
#include "GameManager.hpp"
#include "VfxColour.hpp"

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
		loadLua("functions.lua");
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
	string fullname = DIRECTORY_SCRIPTS + filename;
	int result = luaL_dofile(myLuaState_, fullname.c_str());
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
		bindPosition_(),
		bindRotation_(),
		bindLocation_(),
		bindGameManager_(),
		bindTagged_(),
		bindVisual_(),
		bindVModel_(),
		bindVfx_(),
		bindVfxColour_(),
		bindObject_(),
		bindRigidBody_(),
		bindCreature_(),
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

luabind::scope Scripting::bindPosition_() {
	return luabind::class_<Position>("Position")
		//.def(luabind::constructor<>())
		//.def("update", &Updateable::update)
		//.property("last_update", &Updateable::getLastupdate)
			.property("x", &Position::getX, &Position::setX)
			.property("y", &Position::getY, &Position::setY)
			.property("z", &Position::getZ, &Position::setZ)
			.def("setXYZ", &Position::setXYZ)
			.def("setPosition", &Position::setPosition)
			.def("getPosition", &Position::getPosition)
			.property("Position", &Position::setPosition, &Position::getPosition)
	;
}

luabind::scope Scripting::bindRotation_() {
	return luabind::class_<Rotation>("Rotation")
		.property("rx", &Rotation::getRotX, &Rotation::setRotX)
		.property("ry", &Rotation::getRotY, &Rotation::setRotY)
		.property("rz", &Rotation::getRotZ, &Rotation::setRotZ)
		.property("angle", &Rotation::getRotAngle, &Rotation::setRotAngle)
	;
}

luabind::scope Scripting::bindLocation_() {
	return luabind::class_<Location, luabind::bases<Position, Rotation> >("Location")
		/*.def(luabind::constructor<>())
		.property("area", &Location::getArea, &Location::setArea)
		.property("location", &Location::getLocation, &Location::setLocation)*/
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
		.def("addVfx", &Visual::addVfx)
		.def("removeVfx", &Visual::removeVfx)
	;
}

luabind::scope Scripting::bindVModel_() {
	return luabind::class_<VModel, Visual>("VModel")
		.def(luabind::constructor<string>())
	;
}

luabind::scope Scripting::bindVfx_() {
	return luabind::class_<Vfx>("Vfx")
		//.def(luabind::constructor<>())
	;
}

luabind::scope Scripting::bindVfxColour_() {
	return luabind::class_<VfxColour, Vfx>("VfxColour")
		.def(luabind::constructor<float, float, float, float>())
		.def("setColour", &VfxColour::setColour)
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
		luabind::class_<Object, luabind::bases<Tagged, Location, Updateable, Visual> >("Object")
			.def(luabind::constructor<>())
			.def("setScript", &Object::setScript)
			.def("getScript", &Object::getScript)
			.def("setVisual", &Object::setVisual)
		;
}

luabind::scope Scripting::bindRigidBody_() {
	return
		luabind::class_<RigidBody, luabind::bases<Object> >("RigidBody")
			.def(luabind::constructor<>())
	;
}

luabind::scope Scripting::bindCreature_() {
	return
		luabind::class_<Creature, luabind::bases<Object, RigidBody> >("Creature")
			.def(luabind::constructor<>())
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
