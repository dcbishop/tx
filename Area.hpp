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
class PointLight;

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
		void setDefaultArea();
		Tile* getTile(const int x, const int y);
		void setTile(const int x, const int y, Tile* tile);
		void setSolid(const int x, const int y, const bool isSolid=true);
		bool isSolid(const int x, const int y);

		void setPhysics(Physics* phy);
		Physics* getPhysics();
		void addObject(Object* object);
		void removeObject(Object* object);
		void draw(Interface* interface);
		void update(const int time);
		void getGridCoord(const float fx, const float fy, int &x, int &y);
		void getWorldCoord(const int gx, const int gy, float &fx, float &fy);
		RigidBody* getSolid(const int x, const int y);
		void setRotation(const int x, const int y, float rotation);
		float getRotation(const int x, const int y);
		float getAreaWorldWidth();
		float getAreaWorldHeight();


		void fill(const int x1, const int y1, const int x2, const int y2, const string filename, const bool solidity=false, const float rotation = 0.0f);
		void boxRoom(const int x1, const int y1, const int x2, const int y2);
		Location getLocationFromGridCoord(const int x, const int y);

	private:
		void*** regrowArray_(void*** array, int old_width, int old_height, int width, int height);
		int height_;
		int width_;
		Tile ***tiles_;
		RigidBody ***walkblockers_;
		Physics* physics_;
		btCollisionShape* clipbox_;
		vector<PointLight*> lights_;
};

#endif /* TX_AREA_HPP */
