#ifndef TX_AREA_HPP
#define TX_AREA_HPP

const float TILEWIDTH = 1.0f;

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#include <rcbc.h>

#include "ResourceManager.hpp"

#include "Updateable.hpp"
#include "Physics.hpp"
#include "Container.hpp"
#include "Tagged.hpp"
#include "Visual.hpp"
#include "VModel.hpp"

class GameManager;
class Tile;
class Object;
class RigidBody;

using namespace std;

/**
 * A game area. A load of tiles and objects.
 */
class Area : public Tagged, public Updateable, public Contained, public Visual, public Container {
	public:
		Area(const string tag = DEFAULT_TAG);
		~Area();
		int getHeight();
		void setHeight(float height);
		int getWidth();
		void setWidth(float width);
		void setSize(int width, int height);
		void loadFile(const string filename);
		Tile* getTile(const int x, const int y);
		void setTile(const int x, const int y, Tile* tile);
		void setSolid(const int x, const int y, const bool isSolid=true);
		bool isSolid(const int x, const int y);

		void setPhysics(Physics& phy);
		Physics* getPhysics();
		void addObject(Object& object);
		void removeObject(Object& object);
		void draw(ResourceManager& rm_);
		void update(const int time);
		void getGridCord(const float fx, const float fy, int &x, int &y);
		void getWorldCord(const int gx, const int gy, float &fx, float &fy);
		RigidBody* getSolid(const int x, const int y);
		void boxRoom(int start_x, int start_y, int size);

	private:
		int height_;
		int width_;
		Tile **tiles_;
		RigidBody **walkblockers_;
		Physics* physics_;
		btCollisionShape* clipbox_;
};

#endif /* TX_AREA_HPP */
