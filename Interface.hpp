#ifndef TX_INTERFACE_HPP
#define TX_INTERFACE_HPP

#include <string>
using namespace std;

class Interface {
	private:
		bool finished_;
		int width_;
		int height_;

	public:
		Interface(int width, int height);
		~Interface();
		void SetTitle(string title);
		void MainLoop();
		void CheckEvents();
};

#endif
