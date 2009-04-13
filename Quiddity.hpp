#include <string>
using namespace std;

const string DEFAULT_TAG = "[NULL]";

/**
 * A object class for tagged objects. Just about all in game things
 * should derive from this. http://en.wikipedia.org/wiki/Quiddity
 */
class Quiddity {
	public:
		Quiddity(string tag = DEFAULT_TAG);
		string getTag();
		void setTag(string tag);
	private:
		string tag_;
};
