#include <iostream>
#include <string>

using namespace std;
using std::string;

#include <iostream>

#include <rcbc.h>
#include "console.h"

#include "Area.hpp"
#include "Interface.hpp"
#include "ResourceManager.hpp"
#include "Physics.hpp"
#include "RigidBody.hpp"
#include "Scripting.hpp"
#include "FileProcessor.hpp"
#include "VfxColour.hpp"
#include "VfxVisual.hpp"
#include "VfxOffset.hpp"
#include "Light.hpp"


/**
 * Let there be main...
 */
int main(int argc, char* argv[]) {
	LOG("TX starting...");

	ResourceManager rm;
	GameManager gm;
	DEBUG_A("GameManager created...");

	Area sokoban1("Sokoban1");
	gm.registerObject(&sokoban1);
	FileProcessor::loadArea("data/areas/sokoban1.xml", &sokoban1);

	Area sokoban2("Sokoban2");
	gm.registerObject(&sokoban2);
	FileProcessor::loadArea("data/areas/sokoban2.xml", &sokoban2);

	Area area("start-area.xml");
	gm.registerObject(&area);
	DEBUG_A("Area created...");
	
	Area debugArea("DebugArea");
	gm.registerObject(&debugArea);
	FileProcessor::loadArea("data/areas/debug-area.xml", &debugArea);

	/*Light test("TestLight");
	test.diffuse.setColour(1.0, 0.0, 0.0);
	test.setTempory(true);
	test.setXYZ(0.0, 1.0, 0.0);
	area.addObject(&test);*/

	Interface interface(800, 600);
	DEBUG_A("Interface created 1...");
	interface.setResourceManager(&rm);
	DEBUG_A("Interface created 2...");

	RCBC_Init();

	Creature player("Player");
	player.setTempory(true);

	player.setVisual(new VModel(MODEL_ROBOT));
	//player.setXYZ(0.0f, 2.5f, 0.0f);
	//gm.registerObject(player);
	VfxOffset playerOffset(0.0, -0.2, 0.0);
	player.addVfx(&playerOffset);
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

	area.setDefaultArea();
	FileProcessor::loadArea("data/areas/start-area.xml", &area);
	//area.addObject(player);
	//area.addObject(*testobj);
	//area.addObject(ground);

	// If the area doesn't have a player spawn, make one in the middle
	Object* playerSpawn = area.getObjectByTag("PlayerSpawn");
	if(!playerSpawn) {
		float fx, fz;
		area.getWorldCoord((area.getWidth()/2), area.getHeight()/2, fx, fz);
		playerSpawn = new Object("PlayerSpawn");
		playerSpawn->setXYZ(fx, 0.5, fz);
		playerSpawn->setVisual(new VModel("pointer.dae"));
		playerSpawn->setVisible(false);
		area.addObject(playerSpawn);
	}

	Location spawnLocation = playerSpawn->getLocation();
	spawnLocation.setY(spawnLocation.getY() + 1.0f);
	player.setLocation(spawnLocation);
	//player.addVfx(new VfxColour(0.0f, 1.0f, 0.0f, 0.5f));
	//VfxVisual* vfxTest = new VfxVisual(new VModel("cube.dae"));
	//vfxTest->setY(1.0f);

	//player.addVfx(vfxTest);

	interface.setCreature(player);
	interface.mainLoop();

	// Save the last area
	Area* last_area = player.getArea();
	FileProcessor::saveArea(*last_area, "data/areas/last-edited.xml");

	LOG("TX finished...");

	exit(EXIT_SUCCESS);
	return 0;
}
