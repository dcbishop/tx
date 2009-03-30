#ifndef TX_AREA_HPP
#define TX_AREA_HPP

const float TILEWIDTH = 1.0f;

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
		Model* getTile(const int x, const int y);
		void setTile(const int x, const int y, Model* tile);
		void setResourceManager(ResourceManager* rm);
		void Draw();

	private:
		int setHeight(const int height);
		int setWidth(const int width);

		int height_;
		int width_;
		int x_offset_;
		int y_offset_;
		
		Model **tiles_;
		ResourceManager* rm_;
};

#endif
