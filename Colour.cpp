#include "Colour.hpp"

Colour::Colour() {
	setColour();
}

void Colour::setColour(float nred, float ngreen, float nblue, float nalpha) {
	red = red;
	green = green;
	blue = blue;
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
