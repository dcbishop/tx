#include <iostream>
#include <string>

using namespace std;
using std::string;

#include "Area.hpp"
#include "Interface.hpp"
#include "ImageManager.hpp"
#include "console.h"
#include <rcbc.h>

int main(int argc, char* argv[]) 
{
	LOG("TX starting...");
	
	ImageManager imageManager;
	
	Model model;
	
	Area area;
	string filename = "data/areas/test-area.xml";
	area.LoadFile(&model, &imageManager.images, filename);
	
	Interface* interface = new Interface(800, 600);
	interface->MainLoop();
	delete(interface);
	
	LOG("TX finished...");
	return 0;
}
