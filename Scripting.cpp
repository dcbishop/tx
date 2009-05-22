#include "Scripting.hpp"

#include <luabind/out_value_policy.hpp>

#include "console.h"
#include "Location.hpp"
#include "Position.hpp"
#include "Object.hpp"
#include "RigidBody.hpp"
#include "GameManager.hpp"
#include "VfxColour.hpp"
#include "VfxScripted.hpp"
#include "Tile.hpp"
#include "Container.hpp"
#include "FileProcessor.hpp"
#include "Light.hpp"

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
		//luabind::def("getMemoryAddress", Scripting::getMemoryAddress_),
		luabind::def("loadArea", FileProcessor::loadArea)
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
		DEBUG_A("%s", filename.c_str());
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

/*long Scripting::getMemoryAddress_(void* ptr) {
	return (long)ptr;
}*/

void Scripting::bindAll_() {
	luabind::module(myLuaState_) [
		bindBullet_(),
		bindColour_(),
		bindUpdateable_(),
		bindContainer_(),
		bindContained_(),
		bindPosition_(),
		bindRotation_(),
		bindLocation_(),
		bindGameManager_(),
		bindTagged_(),
		bindVisual_(),
		bindVModel_(),
		bindTile_(),
		bindVfx_(),
		bindVfxColour_(),
		bindVfxScripted_(),
		bindObject_(),
		bindRigidBody_(),
		bindCreature_(),
		bindArea_()
	];
	luabind::bind_class_info(myLuaState_); 
}

luabind::scope Scripting::bindBullet_() {
	return luabind::class_<btCollisionShape>("btCollisionShape")
	;
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
		.def("getRigidBodyByTag", &Container::getRigidBodyByTag)
		.def("getCreatureByTag", &Container::getCreatureByTag)
		.def("getNearestObjectTo", &Container::getNearestObjectTo)
		.def("getNearestObjectByTag", &Container::getNearestObjectByTag)
	;
}

luabind::scope Scripting::bindContained_() {
	return luabind::class_<Contained>("Contained")
		.def("getMemoryAddress", &Contained::getMemoryAddress)
	;
}

luabind::scope Scripting::bindColour_() {
	return luabind::class_<Colour>("Colour")
		.def("getRed", &Colour::getRed)
		.def("getGreen", &Colour::getRed)
		.def("getBlue", &Colour::getRed)
		.def("setColour", &Colour::setColour)
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
			.def("getDistanceTo", &Position::getDistanceTo)
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
	return luabind::class_<Location, luabind::bases<Position, Rotation, Contained> >("Location")
		.def(luabind::constructor<>())
		.property("area", &Location::getArea, &Location::setArea)
		.property("location", &Location::getLocation, &Location::setLocation)
		.property("rotation", &Location::getRotation, &Location::setRotation)
		.def("getDistanceTo", &Location::getDistanceTo)
		.def("getDistanceTo2D", &Location::getDistanceTo2D)
		.def("getGridX", &Location::getGridX)
		.def("getGridY", &Location::getGridY)
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

luabind::scope Scripting::bindTile_() {
	return luabind::class_<Tile, VModel, Contained>("Tile")
		.def(luabind::constructor<string>())
	;
}

luabind::scope Scripting::bindVfx_() {
	return luabind::class_<Vfx, Contained>("Vfx")
		//.def(luabind::constructor<>())
	;
}

luabind::scope Scripting::bindVfxColour_() {
	return luabind::class_<VfxColour, luabind::bases<Vfx, Colour> >("VfxColour")
		.def(luabind::constructor<float, float, float, float>())
	;
}

luabind::scope Scripting::bindVfxScripted_() {
	return luabind::class_<VfxScripted, luabind::bases<Vfx, Updateable> >("VfxScripted")
		.def(luabind::constructor<string>())
		.def("getVfx", &VfxScripted::getVfx)
		.def("setVfx", &VfxScripted::setVfx)
	;
}

luabind::scope Scripting::bindGameManager_() {
	return
		luabind::class_<GameManager, luabind::bases<Updateable, Container> >("GameManager")
			.def("registerObject", &GameManager::registerObject)
			//.def(luabind::constructor<>())
		;
}

luabind::scope Scripting::bindObject_() {
	return
		luabind::class_<Object, luabind::bases<Tagged, Location, Updateable, Visual> >("Object")
			.def(luabind::constructor<string, Visual*>())
			.def("setScript", &Object::setScript)
			.def("getScript", &Object::getScript)
			.def("setVisual", &Object::setVisual)
			.def("getVisual", &Object::getVisual)
			//.def("addVfx", &Object::addVfx)
			//.def("removeVfx", &Object::addVfx)
		;
}

luabind::scope Scripting::bindLight_() {
	return
		luabind::class_<Light, luabind::bases<Object> >("Light")
			.def(luabind::constructor<string, Visual*>())
	;
}

luabind::scope Scripting::bindRigidBody_() {
	return
		luabind::class_<RigidBody, luabind::bases<Object> >("RigidBody")
			.def(luabind::constructor<string, Visual*>())
			.def("setShape", &RigidBody::setShape)
			.def("setMass", &RigidBody::setMass)
			.def("setFriction", &RigidBody::setFriction)
			.def("loadShapeBox", &RigidBody::loadShapeBox)
			.def("loadShapeFromModel", &RigidBody::loadShapeFromModel)
			.def("disableRotation", &RigidBody::disableRotation)
			.def("setKinematic", &RigidBody::setKinematic)
	;
}

luabind::scope Scripting::bindCreature_() {
	return
		luabind::class_<Creature, luabind::bases<Object, RigidBody> >("Creature")
			.def(luabind::constructor<string, Visual*>())
	;
}

luabind::scope Scripting::bindArea_() {
	return
		luabind::class_<Area, luabind::bases<Tagged, Contained, Updateable, Container> >("Area")
			.def(luabind::constructor<>())
			.property("width", &Area::getWidth, &Area::setWidth)
			.property("height", &Area::getHeight, &Area::setHeight)
			.def("setSize", &Area::setSize)
			.def("setDefaultArea", &Area::setDefaultArea)
			.def("fill", &Area::fill)
			.def("boxRoom", &Area::boxRoom)
			.def("addObject", &Area::addObject)
			.def("removeObject", &Area::removeObject)
			.def("setSolid", &Area::setSolid)
			.def("isSolid", &Area::isSolid)
			.def("getTile", &Area::getTile)
			.def("setTile", &Area::setTile)
			.def("getLocationFromGridCoord", &Area::getLocationFromGridCoord)
			.def("getLocation", &Area::getLocation)
			//.def_readonly("getGridCoord", &Area::getGridCoord, luabind::pure_out_value(_3) + luabind::pure_out_value(_4))
			//.def("getWorldCoord", &Area::getWorldCoord)
	;
}
