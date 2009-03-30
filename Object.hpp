#ifndef TX_OBJECT_HPP
#define TX_OBJECT_HPP

#include <rcbc.h>

class Object {
	public:
		Object();
		~Object();
		void Update(const int time);
		void Draw();
		void setPos(const float x, const float y, const float z);
		void setX(const float x);
		void setY(const float y);
		void setZ(const float z);
		const float getX();
		const float getY();
		const float getZ();
		void setRotX(const float rx);
		void setRotY(const float ry);
		void setRotZ(const float rz);
		void setRotAngle(const float z);
		const float getRotX();
		const float getRotY();
		const float getRotZ();
		const float getRotAngle();
		const float getLastUpdate();
		void setModel(const Model* model);

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
};

#endif
