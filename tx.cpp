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

	Scripting sc;

	Area area;
	area.setResourceManager(rm);
	gm.Register(area);

	Interface interface(800, 600);
	RCBC_Init();
	//Physics physics;

	Creature player("Player");
	//Model* playermod = RCBC_LoadFile("data/models/monkey-robot.dae", rm.getImages());
	//player.setShape(new btBoxShape(btVector3(.5,.5,.5)));
	Model* playermod = rm.loadModel("data/models/monkey-robot.dae");
	player.setModel(*playermod);
	player.setPos(0.0f, 6.5f, 0.0f);
	gm.Register(player);

	Model* testobjmod = rm.loadModel("data/models/unmaptest.dae");
	Object testobj;
	testobj.setModel(*testobjmod);
	testobj.setPos(-3.0f, 0.0f, 0.0f);
	gm.Register(testobj);

	Model* grass = rm.loadModel("data/models/mayagrass.dae");
	RigidBody ground;
	ground.setMass(0);
	ground.setShape(new btStaticPlaneShape(btVector3(0,1,0), 0));
	ground.setModel(*grass);	
	ground.setPos(-1.0f, 0.0f, -1.0f);
	gm.Register(ground);

	//area.setPhysics(&physics);
	area.setPhysics(gm.getPhysics());
	area.LoadFile("data/areas/test-area.xml");
	area.addObject(player);
	area.addObject(ground);
	area.addObject(testobj);

	interface.setCreature(player);
	interface.setGameManager(gm);

	interface.MainLoop();

	rm.unloadModel(playermod);
	rm.unloadModel(testobjmod);
	rm.unloadModel(grass);

	LOG("TX finished...");

	return 0;
}
