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
	Interface* interface = new Interface(800, 600);
	RCBC_Init();
	area.LoadFile("data/areas/test-area.xml");
	interface->setArea(&area);
	interface->MainLoop();

	delete(interface);

	LOG("TX finished...");
	return 0;
}
