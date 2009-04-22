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

	//Scripting sc;

	Area area("TestArea");
	//area.setResourceManager(rm);
	gm.Register(area);
	
	Interface interface(800, 600);
	interface.setResourceManager(rm);

	RCBC_Init();
	//Physics physics;

	Creature player("Player");
	player.setTempory(true);
	//Model* playermod = RCBC_LoadFile("data/models/monkey-robot.dae", rm.getImages());
	//player.setShape(new btBoxShape(btVector3(.5,.5,.5)));
	//Model* playermod = rm.loadModel("data/models/monkey-robot.dae");
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
	
	//Model* grass = rm.loadModel("data/models/mayagrass.dae");
	//VModel grassvis("data/models/mayagrass.dae");
	RigidBody ground("TestGround");
	ground.setMass(0);
	//ground.setFriction(0.0f);
	ground.setShape(new btStaticPlaneShape(btVector3(0,1,0), 0));
	//ground.setVisual(grassvis);
	ground.setPos(1.0f, 0.0f, 1.0f);
	ground.setScript(SCRIPT_ONupdate, "data/scripts/test.lua");
	gm.Register(ground);

	//area.setPhysics(&physics);
	area.setPhysics(gm.getPhysics());
	area.loadFile("data/areas/test-area.xml");
	area.addObject(player);
	area.addObject(ground);
	area.addObject(testobj);

	interface.setCreature(player);
	//interface.setGameManager(gm);
	interface.mainLoop();

	/*rm.unloadModel(playermod);
	rm.unloadModel(testobjmod);
	rm.unloadModel(grass);*/

	LOG("TX finished...");

	return 0;
}
