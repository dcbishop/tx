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
#include "console.h"

/**
 * Let there be main...
 */
int main(int argc, char* argv[]) {
	LOG("TX starting...");

	/*Editor edit;
	edit.show();
	while(true) {
		edit.processQtEvents();
	}*/

	ResourceManager rm;
	GameManager gm;

	Area area("TestArea");
	gm.Register(area);

	Interface interface(800, 600);
	interface.setResourceManager(rm);

	RCBC_Init();

	Creature player("Player");
	player.setTempory(true);
	VModel playervis("data/models/monkey-robot.dae");
	player.setVisual(playervis);
	player.setPos(7.0f, 2.5f, 7.0f);
	gm.Register(player);


	VModel testobjvis("data/models/cube.dae");
	Object testobj("TestObject1");
	testobj.setTempory(true);
	testobj.setVisual(testobjvis);
	testobj.setPos(5.0f, 0.125f, 5.0f);
	testobj.setScript(SCRIPT_ONupdate, "data/scripts/test.lua");
	gm.Register(testobj);

	//VModel grassvis("data/models/mayagrass.dae");
	RigidBody ground("TestGround");
	ground.setMass(0);
	//ground.setFriction(0.0f);
	ground.setShape(new btStaticPlaneShape(btVector3(0,1,0), 0));
	//ground.setVisual(grassvis);
	ground.setPos(1.0f, 0.0f, 1.0f);
	ground.setScript(SCRIPT_ONupdate, "data/scripts/test.lua");
	gm.Register(ground);

#warning ['TODO']: Either set this when added to GameManager or pull it from there when needed in Area
	area.setPhysics(gm.getPhysics());

	area.loadFile("data/areas/test-area.xml");
	area.addObject(player);
	area.addObject(ground);
	area.addObject(testobj);

	interface.setCreature(player);
	interface.mainLoop();

	LOG("TX finished...");

	return 0;
}
