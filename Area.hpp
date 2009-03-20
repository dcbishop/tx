#ifndef TX_AREA_HPP
#define TX_AREA_HPP

#include <iostream>
#include <string.h>

#include <rcbc.h>

using namespace std;

class Area {
	public:
		~Area();
		int getHeight();
		int getWidth();
		void LoadFile(Model* model, List* images, string filename);
		int getTile(int x, int y);
		void setTile(int x, int y, int tile);
		void Draw();

	private:
		int setHeight(int height);
		int setWidth(int width);
		
		int height_;
		int width_;
		int *tiles_;
};

#endif
