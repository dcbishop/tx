#include <vector>
#include <map>

using namespace std;

/**
 * A class that is responsible for all the ingame stuff.
 * Doesn't handle the rendering.
 */
class {
	public:
		void Update();

	private:
		Scripting scripting_;
		Physics physics_;
		vector<Area*> areas_;
		multimap<string, Quiddity*> tags_;		
}
