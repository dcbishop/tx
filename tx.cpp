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
	gm.Register(area);
	DEBUG_A("Area created...");

	Interface interface(800, 600);
	DEBUG_A("Interface created 1...");
	interface.setResourceManager(&rm);
	DEBUG_A("Interface created 2...");


	RCBC_Init();

	Creature player("Player");
	player.setTempory(true);
	VModel playervis("data/models/monkey-robot.dae");
	player.setVisual(playervis);
	player.setPos(7.0f, 2.5f, 7.0f);
	gm.Register(player);
	DEBUG_A("Player created...");

	VModel testobjvis("data/models/cube.dae");
	Object testobj("TestObject");
	testobj.setTempory(true);
	testobj.setVisual(testobjvis);
	testobj.setPos(5.0f, 0.125f, 5.0f);
	testobj.setScript(SCRIPT_ONUPDATE, "data/scripts/test.lua");
	gm.Register(testobj);

	//VModel grassvis("data/models/mayagrass.dae");
	RigidBody ground("TestGround");
	ground.setTempory(true);
	ground.setMass(0);
	//ground.setFriction(0.0f);
	ground.setShape(new btStaticPlaneShape(btVector3(0,1,0), 0));
	//ground.setVisual(grassvis);
	ground.setPos(1.0f, 0.0f, 1.0f);
	//ground.setScript(SCRIPT_ONUPDATE, "data/scripts/test.lua");
	gm.Register(ground);

#warning ['TODO']: Either set this when added to GameManager or pull it from there when needed in Area
	area.setPhysics(gm.getPhysics());

	area.loadFile("data/areas/test-area.xml");
	FileProcessor::loadArea("data/areas/test-area.xml", &area);
	area.addObject(player);
	area.addObject(ground);
	area.addObject(testobj);

	interface.setCreature(player);
	interface.mainLoop();
	FileProcessor::saveArea(area, "data/areas/test-area.xml");

	LOG("TX finished...");

	return 0;
}
