#ifndef TX_TAGGED_HPP
#define TX_TAGGED_HPP

#include <string>
using namespace std;

class GameManager;

const string DEFAULT_TAG = "[NULL]";

/**
 * A abstract class for tagged objects. Just about all ingame things
 * should derive from this.
 */
class Tagged {
	public:
		Tagged(string tag = DEFAULT_TAG);
		virtual const string getTag();
		virtual void setTag(const string tag);
		GameManager* getGameManager();
		void setGameManager(GameManager* gm);
		
	private:
		string tag_;
		GameManager* gm_;
};

#endif
