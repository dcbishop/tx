#include "Colour.hpp"

Colour::Colour() {
	setColour(1.0, 1.0, 1.0, 1.0);
}

void Colour::setColour(float nred, float ngreen, float nblue, float nalpha) {
	red = nred;
	green = ngreen;
	blue = nblue;
	alpha = nalpha;
}

float Colour::getRed() {
	return red;
}

float Colour::getGreen() {
	return green;
}

float Colour::getBlue() {
	return blue;
}

float Colour::getAlpha() {
	return alpha;
}
