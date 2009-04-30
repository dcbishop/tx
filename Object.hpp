#ifndef TX_OBJECT_HPP
#define TX_OBJECT_HPP

#include <stdlib.h>
#include <rcbc.h>

class Object;
#include "Area.hpp"
#include "Tagged.hpp"
#include "Updateable.hpp"
#include "Container.hpp"
#include "Visual.hpp"

const int NUM_SCRIPTS = 1;
const int SCRIPT_ONUPDATE = 1;

/**
 * An ingame object. Has a visual model, cordinates, rotation and
 * attached area.
 */
class Object : public Tagged, public Updateable, public Contained, public Visual {
	public:
		Object(string tag = DEFAULT_TAG, Visual* model = NULL);
		~Object();
		virtual Object* clone() {return new Object(*this);} /**< Copy constructor */
		virtual void draw(ResourceManager& rm);
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
		void setVisual(Visual& visual);
		Visual& getVisual();
		virtual void setArea(Area& area);
		virtual Area* getArea();
		virtual void setScript(const int type, const string filename);
		virtual string getScript(const int type);

		void update(const int time);

	private:
		float x_;
		float y_;
		float z_;

		float rx_;
		float ry_;
		float rz_;
		float angle_;
		string scripts_[NUM_SCRIPTS];

		Visual* visual_;
};

#endif /* TX_OBJECT_HPP */
