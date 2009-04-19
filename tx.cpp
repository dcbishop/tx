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
	//Model* playermod = RCBC_LoadFile("data/models/monkey-robot.dae", rm.getImages());
	//player.setShape(new btBoxShape(btVector3(.5,.5,.5)));
	//Model* playermod = rm.loadModel("data/models/monkey-robot.dae");
	VModel playervis("data/models/monkey-robot.dae");
	player.setVisual(playervis);
	player.setPos(7.0f, 2.5f, 7.0f);
	
	gm.Register(player);

	//Model* testobjmod = rm.loadModel("data/models/unmaptest.dae");
	VModel testobjvis("data/models/cube.dae");
	
	/*Object testobj1("TestObject1");
	testobj1.setVisual(testobjvis);
	testobj1.setPos(5.0f, 0.125f, 5.0f);
	Object testobj2("TestObject1");
	testobj2.setVisual(testobjvis);
	testobj2.setPos(5.0f, 0.125f, 6.0f);
	Object testobj3("TestObject1");
	testobj3.setVisual(testobjvis);
	testobj3.setPos(6.0f, 0.125f, 5.0f);
	Object testobj4("TestObject1");
	testobj4.setVisual(testobjvis);
	testobj4.setPos(7.1f, 0.125f, 5.7f);
	Object testobj5("TestObject1");
	testobj5.setVisual(testobjvis);
	testobj5.setPos(5.3f, 0.125f, 7.6f);
	Object testobj6("TestObject1");
	testobj6.setVisual(testobjvis);
	testobj6.setPos(4.5f, 0.125f, 4.3f);
	Object testobj7("TestObject1");
	testobj7.setVisual(testobjvis);
	testobj7.setPos(4.4f, 0.125f, 4.2f);
	Object testobj8("TestObject1");
	testobj8.setVisual(testobjvis);
	testobj8.setPos(4.1f, 0.125f, 4.1f);
	Object testobj9("TestObject1");
	testobj9.setVisual(testobjvis);
	testobj9.setPos(4.3f, 0.125f, 4.2f);
	Object testobj10("TestObject1");
	testobj10.setVisual(testobjvis);
	testobj10.setPos(4.5f, 0.125f, 4.7f);

	//BREAK();
	//testobj.setX(3.0);
	
	testobj1.setScript(SCRIPT_ONUPDATE, "data/scripts/runaway.lua");
	testobj2.setScript(SCRIPT_ONUPDATE, "data/scripts/runaway.lua");
	testobj3.setScript(SCRIPT_ONUPDATE, "data/scripts/runaway.lua");
	testobj4.setScript(SCRIPT_ONUPDATE, "data/scripts/runaway.lua");
	testobj5.setScript(SCRIPT_ONUPDATE, "data/scripts/runaway.lua");
	testobj6.setScript(SCRIPT_ONUPDATE, "data/scripts/runaway.lua");
	testobj7.setScript(SCRIPT_ONUPDATE, "data/scripts/runaway.lua");
	testobj8.setScript(SCRIPT_ONUPDATE, "data/scripts/runaway.lua");
	testobj9.setScript(SCRIPT_ONUPDATE, "data/scripts/runaway.lua");
	testobj10.setScript(SCRIPT_ONUPDATE, "data/scripts/runaway.lua");
	gm.Register(testobj1);
	gm.Register(testobj2);
	gm.Register(testobj3);
	gm.Register(testobj4);
	gm.Register(testobj5);
	gm.Register(testobj6);
	gm.Register(testobj7);
	gm.Register(testobj8);
	gm.Register(testobj9);
	gm.Register(testobj10);*/

	//Model* grass = rm.loadModel("data/models/mayagrass.dae");
	//VModel grassvis("data/models/mayagrass.dae");
	RigidBody ground("TestGround");
	ground.setMass(0);
	//ground.setFriction(0.0f);
	ground.setShape(new btStaticPlaneShape(btVector3(0,1,0), 0));
	//ground.setVisual(grassvis);
	ground.setPos(1.0f, 0.0f, 1.0f);
	gm.Register(ground);

	//area.setPhysics(&physics);
	area.setPhysics(gm.getPhysics());
	area.LoadFile("data/areas/test-area.xml");
	area.addObject(player);
	area.addObject(ground);

	interface.setCreature(player);
	interface.setGameManager(gm);
	interface.MainLoop();

	/*rm.unloadModel(playermod);
	rm.unloadModel(testobjmod);
	rm.unloadModel(grass);*/

	LOG("TX finished...");

	return 0;
}
