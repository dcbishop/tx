#include <iostream>
#include <string>

using namespace std;
using std::string;

#include <iostream>

#include <rcbc.h>

#include "Area.hpp"
#include "Interface.hpp"
#include "ResourceManager.hpp"
#include "Physics.hpp"
#include "RigidBody.hpp"
#include "Scripting.hpp"
#include "FileProcessor.hpp"
#include "VfxColour.hpp"
#include "VfxVisual.hpp"
#include "console.h"


/**
 * Let there be main...
 */
int main(int argc, char* argv[]) {
	LOG("TX starting...");

	ResourceManager rm;
	GameManager gm;
	DEBUG_A("GameManager created...");

	Area area("TestArea");
	gm.registerObject(area);
	DEBUG_A("Area created...");

	Interface interface(800, 600);
	DEBUG_A("Interface created 1...");
	interface.setResourceManager(&rm);
	DEBUG_A("Interface created 2...");


	RCBC_Init();

	Creature player("Player");
	player.setTempory(true);

	player.setVisual(new VModel("monkey-robot.dae"));
	//player.setXYZ(0.0f, 2.5f, 0.0f);
	//gm.registerObject(player);
	DEBUG_A("Player created...");

	//Object* testobj = new Object("TestRigid");
	RigidBody* testobj = new RigidBody("TestRigid");
	testobj->setTempory(true);
	testobj->setVisual(new VModel("cube.dae"));
	testobj->setShape(new btBoxShape(btVector3(.125,.125,.125)));
	testobj->setXYZ(2.0f, 2.0f, 2.0f);
	//testobj.setTempory(true);
	//testobj->setXYZ(7.0f, 5.125f, 7.0f);
	//testobj->setScript(SCRIPT_ONUPDATE, "test.lua");
	//gm.registerObject(*testobj);
	//area.addObject(*testobj);

	RigidBody ground("TestGround");
	ground.setTempory(true);
	ground.setMass(0);
	//ground.setFriction(0.0f);
	ground.setShape(new btStaticPlaneShape(btVector3(0,1,0), 0));
	//ground.setVisual(new VModel("mayagrass.dae"));
	ground.setVisible(false);
	ground.setXYZ(1.0f, 0.0f, 1.0f);


#warning ['TODO']: Either set this when added to GameManager or pull it from there when needed in Area
	area.setPhysics(gm.getPhysics());

	area.setDefaultArea();
	FileProcessor::loadArea("data/areas/test-area.xml", &area);
	area.addObject(player);
	area.addObject(*testobj);
	area.addObject(ground);

	// If the area doesn't have a player spawn, make one in the middle
	Object* playerSpawn = area.getObjectByTag("PlayerSpawn");
	if(!playerSpawn) {
		float fx, fz;
		area.getWorldCoord((area.getWidth()/2), area.getHeight()/2, fx, fz);
		playerSpawn = new Object("PlayerSpawn");
		playerSpawn->setXYZ(fx, 0.5, fz);
		playerSpawn->setVisual(new VModel("pointer.dae"));
		area.addObject(*playerSpawn);
	}

	Location spawnLocation = playerSpawn->getLocation();
	spawnLocation.setY(spawnLocation.getY() + 1.0f);
	player.setLocation(spawnLocation);
	//player.addVfx(new VfxColour(0.0f, 1.0f, 0.0f, 1.0f));
	VfxVisual* vfxTest = new VfxVisual(new VModel("cube.dae"));
	vfxTest->setY(1.0f);

	player.addVfx(vfxTest);

	interface.setCreature(player);
	interface.mainLoop();

	FileProcessor::saveArea(area, "data/areas/test-area.xml");

	LOG("TX finished...");

	return 0;
}
