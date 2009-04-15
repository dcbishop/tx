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
#include "Container.hpp"
#include "Tagged.hpp"

using namespace std;

typedef Model Tile;
/**
 * A game area. A load of tiles and objects.
 */
class Area  : public Tagged, public Updateable, public Contained {
	public:
		Area();
		~Area();
		int getHeight();
		int getWidth();
		void setSize(int width, int height);
		void LoadFile(string filename);
		Tile* getTile(const int x, const int y);
		void setTile(const int x, const int y, Tile* tile);
		void setResourceManager(ResourceManager& rm);
		ResourceManager* getResourceManager();
		void setPhysics(Physics& phy);
		Physics* getPhysics();
		void addObject(Object& object);
		void removeObject(Object& object);
		void Draw();
		void Update(const int time);
		void getGridCord(const float fx, const float fy, int &x, int &y);
		void getWorldCord(const int gx, const int gy, float &fx, float &fy);


	private:
		int height_;
		int width_;
		
		Model **tiles_;
		vector<Object*> objects_;
		ResourceManager* rm_;
		Physics* physics_;
};

#endif
