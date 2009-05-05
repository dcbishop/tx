#ifndef TX_TILE_HPP
#define TX_TILE_HPP

class Area;
#include "VModel.hpp"
#include "Container.hpp"
#include "Physics.hpp"

const string TILE_VOID = "void.dae";
const string TILE_WALL = "Wall.dae";
const string TILE_FLOOR = "floor.dae";
const string TILE_INNERCORNER = "inner corner.dae";
/**
 * A tile for use in an area.
 */
class Tile : public VModel, public Contained {
	public:
		Tile(const string filename);
		~Tile();
		void setRotation(float rotation);
		float getRotation();
		void draw(Interface* interface);
		/*void setSolid(btRigidBody* clip);
		btRigidBody* getSolid();*/
		Area* getArea();

	private:
		void removeRigidBody_();
		void addRigidBody_();
		float rotation_;
		btRigidBody* clip_;
};
#endif /* TX_TILE_HPP */
