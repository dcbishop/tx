#ifndef TX_OBJECT_HPP
#define TX_OBJECT_HPP

#include <rcbc.h>

class Area;
#include "Area.hpp"

class Object {
	public:
		Object();
		~Object();
		virtual void Update(const int time);
		virtual void Draw();
		virtual void setPos(const float x, const float y, const float z);
		virtual void setX(const float x);
		virtual void setY(const float y);
		virtual void setZ(const float z);
		virtual const float getX();
		virtual const float getY();
		virtual const float getZ();
		virtual void setRotX(const float rx);
		virtual void setRotY(const float ry);
		virtual void setRotZ(const float rz);
		virtual void setRotAngle(const float z);
		virtual const float getRotX();
		virtual const float getRotY();
		virtual const float getRotZ();
		virtual const float getRotAngle();
		virtual const float getLastUpdate();
		virtual void setModel(const Model* model);
		virtual const Model* getModel();
		virtual void setArea(Area* area);
		virtual Area* getArea();

	private:
		float x_;
		float y_;
		float z_;

		float rx_;
		float ry_;
		float rz_;
		float angle_;

		int last_update_;

		const Model* model_;
		Area* area_;
};

#endif
