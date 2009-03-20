#include "Area.hpp"

int Area::getHeight() {
	return height_;
}

int Area::getWidth() {
	return width_;
}

void Area::LoadFile(Model* model, List* images, string filename) {
	height_ = 10;
	width_ = 10;
	tiles_ = new int[height_*width_];
}

int Area::getTile(int x, int y) {
	return tiles_[(y*width_)+x];
}

void Area::setTile(int x, int y, int tile) {
	tiles_[(y*width_)+x] = tile;
}

void Area::Draw() {
	for(int y = 0; y < height_; y++) {
		for(int x = 0; x < width_; x++) {
			cout << getTile(x, y);
		}
		cout << endl;
	}
}

Area::~Area() {
	delete [] tiles_;
	tiles_ = NULL;
}
