#ifndef TX_OBJECT_HPP
#define TX_OBJECT_HPP

#include <rcbc.h>

class Object;
#include "Area.hpp"
#include "Tagged.hpp"
#include "Updateable.hpp"
#include "Location.hpp"
#include "Container.hpp"
#include "Visual.hpp"

const int NUM_SCRIPTS = 1;
const int SCRIPT_ONUPDATE = 1;

/**
 * An ingame object. Has a visual model, coordinates, rotation and
 * attached area.
 */
class Object : public Tagged, public Updateable, public Visual, public Location {
	public:
		Object(string tag = DEFAULT_TAG, Visual* model = NULL);
		~Object();
		virtual Object* clone() {return new Object(*this);} /**< Copy constructor */
		virtual void draw(Interface* interface);
		void setVisual(Visual* visual);
		Visual& getVisual();
		virtual void setScript(const int type, const string filename);
		virtual string getScript(const int type);
		void update(const int time);
		void addVfx(Vfx* vfx);

	private:
		string scripts_[NUM_SCRIPTS];
		Visual* visual_;
};

#endif /* TX_OBJECT_HPP */
