#ifndef TX_AREA_HPP
#define TX_AREA_HPP

const float TILEWIDTH = 1.0f;

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include <rcbc.h>

#include "ResourceManager.hpp"

class Object;
#include "Updateable.hpp"
#include "Object.hpp"
#include "Physics.hpp"

using namespace std;

typedef Model Tile;
/**
 * A game area. A load of tiles and objects.
 */
class Area  : public Quiddity, public Updateable {
	public:
		Area();
		~Area();
		int getHeight();
		int getWidth();
		void LoadFile(string filename);
		Tile* getTile(const int x, const int y);
		void setTile(const int x, const int y, Tile* tile);
		void setResourceManager(ResourceManager* rm);
		ResourceManager* getResourceManager();
		void setPhysics(Physics* phy);
		Physics* getPhysics();
		void addObject(Object* object);
		void removeObject(Object* object);
		void Draw();
		void Update(int time);


	private:
		int setHeight(const int height);
		int setWidth(const int width);

		int height_;
		int width_;
		
		Model **tiles_;
		vector<Object*> objects_;
		ResourceManager* rm_;
		Physics* physics_;
};

#endif
