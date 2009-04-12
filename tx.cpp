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

int main(int argc, char* argv[]) {
	LOG("TX starting...");
	
	ResourceManager rm;
	Scripting sc;
	
	Area area;
	area.setResourceManager(&rm);

	Interface interface(800, 600);
	RCBC_Init();
	Physics physics;

	Creature player;
	Model* playermod = RCBC_LoadFile("data/models/monkey-robot.dae", rm.getImages());
	//player.setShape(new btBoxShape(btVector3(.5,.5,.5)));
	player.setModel(playermod);
	player.setPos(0.0f, 6.5f, 0.0f);
	Model* testobjmod = RCBC_LoadFile("data/models/unmaptest.dae", rm.getImages());
	Object testobj;
	testobj.setModel(testobjmod);
	testobj.setPos(-3.0f, 0.0f, 0.0f);
	
	
	Model* grass = RCBC_LoadFile("data/models/mayagrass.dae", rm.getImages());

	RigidBody ground;
	ground.setMass(0);
	ground.setShape(new btStaticPlaneShape(btVector3(0,1,0), 0));
	ground.setModel(grass);	
	ground.setPos(-1.0f, 0.0f, -1.0f);
	
	area.setPhysics(&physics);
	area.LoadFile("data/areas/test-area.xml");
	area.addObject(&player);
	area.addObject(&ground);
	area.addObject(&testobj);
	interface.setCreature(&player);

#warning ['TODO']: We should get the area from the controlled creature...
	interface.setArea(&area);
	interface.MainLoop();
		
	//DELETE(playermod);
	//DELETE(textobjmod);
	//DELETE(grass);

	LOG("TX finished...");
	return 0;
}
