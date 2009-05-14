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
	gm.registerObject(area);
	DEBUG_A("Area created...");

	Interface interface(800, 600);
	DEBUG_A("Interface created 1...");
	interface.setResourceManager(&rm);
	DEBUG_A("Interface created 2...");


	RCBC_Init();

	Creature player("Player");
	player.setTempory(true);
	VModel playervis("monkey-robot.dae");
	player.setVisual(playervis);
	//player.setXYZ(0.0f, 2.5f, 0.0f);
	//gm.registerObject(player);
	DEBUG_A("Player created...");

	VModel testobjvis("cube.dae");
	//Object* testobj = new Object("TestRigid");
	RigidBody* testobj = new RigidBody("TestRigid");
	testobj->setTempory(true);
	testobj->setVisual(testobjvis);
	testobj->setShape(new btBoxShape(btVector3(.125,.125,.125)));
	testobj->setXYZ(2.0f, 2.0f, 2.0f);
	//testobj.setTempory(true);
	//testobj->setXYZ(7.0f, 5.125f, 7.0f);
	//testobj->setScript(SCRIPT_ONUPDATE, "test.lua");
	//gm.registerObject(*testobj);
	//area.addObject(*testobj);

	VModel grassvis("mayagrass.dae");
	RigidBody ground("TestGround");
	ground.setTempory(true);
	ground.setMass(0);
	//ground.setFriction(0.0f);
	ground.setShape(new btStaticPlaneShape(btVector3(0,1,0), 0));
	ground.setVisual(grassvis);
	ground.setXYZ(1.0f, 1.0f, 1.0f);
	//ground.setScript(SCRIPT_ONUPDATE, "");
	//gm.registerObject(ground);

#warning ['TODO']: Either set this when added to GameManager or pull it from there when needed in Area
	area.setPhysics(gm.getPhysics());

	area.loadFile("data/areas/test-area.xml");
	FileProcessor::loadArea("data/areas/test-area.xml", &area);
	area.addObject(player);
	area.addObject(*testobj);
	area.addObject(ground);

	// If the area doesn't have a player spawn, make one in the middle
	VModel playerSpawnModel("cube.dae");
	Object* playerSpawn = area.getObjectByTag("PlayerSpawn");
	if(!playerSpawn) {
		float fx, fz;
		area.getWorldCord((area.getWidth()/2), area.getHeight()/2, fx, fz);
		playerSpawn = new Object("PlayerSpawn");
		playerSpawn->setXYZ(fx, 0.5, fz);
		//DEBUG_M("POINT: %d %f, %f, %f", area.getWidth()/2, fx, 1, fz);
		//BREAK();
		playerSpawn->setVisual(playerSpawnModel);
		area.addObject(*playerSpawn);
	}
	//Position spawnPosition = playerSpawn->getPosition();
	//player.setPosition(spawnPosition);
	Location spawnLocation = playerSpawn->getLocation();
	player.setLocation(spawnLocation);

	//player.setXYZ(1.0f, 2.5f, 1.0f);
	//area.removeObject(testobj);

	//delete(testobj);

	interface.setCreature(player);
	interface.mainLoop();

	FileProcessor::saveArea(area, "data/areas/test-area.xml");

	LOG("TX finished...");

	return 0;
}
