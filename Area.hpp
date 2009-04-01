#ifndef TX_AREA_HPP
#define TX_AREA_HPP

const float TILEWIDTH = 1.0f;

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include <rcbc.h>

#include "ResourceManager.hpp"
#include "Object.hpp"

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
		void addObject(Object* object);
		void removeObject(Object* object);
		void Draw();

	private:
		int setHeight(const int height);
		int setWidth(const int width);

		int height_;
		int width_;
		int x_offset_;
		int y_offset_;
		
		Model **tiles_;
		vector<Object*> objects_;
		ResourceManager* rm_;
};

#endif
