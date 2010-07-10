#ifndef TX_LOCATION_HPP
#define TX_LOCATION_HPP

#include "Position.hpp"
#include "Rotation.hpp"
#include "Area.hpp"

/**
 * A Location class, containts Position, Area and Rotation information.
 */
class Location : public Position, public Rotation, public Contained {
	public:
		Location getLocation();
		virtual void setLocation(Location& location);
		virtual void setArea(Area* area);
		virtual Area* getArea();
		virtual const float getDistanceTo(Location& location);
		virtual const float getDistanceTo2D(Location& location);
		virtual const int getGridX();
		virtual const int getGridY();

	private:
		Area* area_;
};

#endif /* TX_LOCATION_HPP */
