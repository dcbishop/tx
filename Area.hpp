#ifndef TX_AREA_HPP
#define TX_AREA_HPP

#define TILEWIDTH 1.0f

#include <iostream>
#include <string.h>

#include <rcbc.h>

#include "ResourceManager.hpp"

using namespace std;

class Area {
	public:
		~Area();
		int getHeight();
		int getWidth();
		void LoadFile(string filename);
		Model* getTile(int x, int y);
		void setTile(int x, int y, Model* tile);
		void setResourceManager(ResourceManager* rm);
		void Draw();

	private:
		int setHeight(int height);
		int setWidth(int width);

		int height_;
		int width_;
		Model **tiles_;
		ResourceManager* rm_;
};

#endif
