#ifndef TX_UPDATEABLE_HPP
#define TX_UPDATEABLE_HPP

/**
 * An abstract class for Objects than can be updated with time.
 */
class Updateable {
	public:
		Updateable();
		virtual void Update(const int time);
		virtual const int getLastUpdate();
	
	private:
		int last_update_;
};

#endif
