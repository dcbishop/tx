#ifndef TX_UPDATEABLE_HPP
#define TX_UPDATEABLE_HPP

/**
 * An abstract class for Objects than can be updated with time.
 */
class Updateable {
	public:
		Updateable();
		virtual void update(const int time);
		virtual const int getLastupdate();

	private:
		int last_update_;
};

#endif /* TX_UPDATEABLE_HPP */
