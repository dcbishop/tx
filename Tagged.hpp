#ifndef TX_TAGGED_HPP
#define TX_TAGGED_HPP

#include <string>
using namespace std;

const string DEFAULT_TAG = "[NULL]";

/**
 * A abstract class for tagged objects. Just about all ingame things
 * should derive from this. http://en.wikipedia.org/wiki/Tagged
 */
class Tagged {
	public:
		Tagged(string tag = DEFAULT_TAG);
		virtual string getTag();
		virtual void setTag(const string tag);
	private:
		string tag_;
};

#endif
