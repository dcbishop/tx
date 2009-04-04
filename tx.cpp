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
	player.setModel(playermod);

	Model* textobjmod = RCBC_LoadFile("data/models/unmaptest.dae", rm.getImages());
	Object testobj;
	testobj.setModel(textobjmod);
	
	area.setPhysics(&physics);
	area.LoadFile("data/areas/test-area.xml");
	area.addObject(&player);
	area.addObject(&testobj);
	
	interface.setCreature(&player);

#warning ['TODO']: We should get the area from the controlled creature...
	interface.setArea(&area);
	interface.MainLoop();
		
	DELETE(playermod);
	DELETE(textobjmod);
	
	LOG("TX finished...");
	return 0;
}
