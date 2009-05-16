#ifndef TX_POSITION_HPP
#define TX_POSITION_HPP

/**
 * An abstract class for objects with x, y, z coordinates.
 */
class Position {
	public:
		virtual Position& getPosition();
		virtual void setPosition(Position& Position);
		virtual void setXYZ(const float x, const float y, const float z);
		virtual const float getX();
		virtual const float getY();
		virtual const float getZ();
		virtual void setX(const float x);
		virtual void setY(const float y);
		virtual void setZ(const float z);
		virtual const float getDistanceTo(Position& position);
		virtual const float getDistanceTo2D(Position& position);
		virtual const float getDirectionTo2D(Position& position);

	private:
		float x_;
		float y_;
		float z_;
};

#endif /* TX_POSITION_HPP */
