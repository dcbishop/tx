#ifndef TX_LOCATABLE_HPP
#define TX_LOCATABLE_HPP

/**
 * A abstract class for objects with x, y, z coordinates.
 */
class Location {
	public:
		virtual Location& getLocation();
		virtual void setLocation(Location& location);
		virtual void setXYZ(const float x, const float y, const float z);
		virtual const float getX();
		virtual const float getY();
		virtual const float getZ();
		virtual void setX(const float x);
		virtual void setY(const float y);
		virtual void setZ(const float z);

	private:
		float x_;
		float y_;
		float z_;
};

#endif /* TX_LOCATABLE_HPP */
