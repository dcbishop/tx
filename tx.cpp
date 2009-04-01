#include <iostream>
#include <string>

using namespace std;
using std::string;

#include <rcbc.h>

#include "Area.hpp"
#include "Interface.hpp"
#include "ResourceManager.hpp"
#include "console.h"

int main(int argc, char* argv[]) 
{
	LOG("TX starting...");

	ResourceManager rm;

	Area area;
	area.setResourceManager(&rm);

	Interface interface(800, 600);
	RCBC_Init();

	Creature player;
	Model* playermod = RCBC_LoadFile("data/models/monkey-robot.dae", rm.getImages());
	player.setModel(playermod);

	area.LoadFile("data/areas/test-area.xml");
	area.addObject(&player);
	interface.setCreature(&player);
	interface.setArea(&area);
	interface.MainLoop();

	LOG("TX finished...");
	return 0;
}
