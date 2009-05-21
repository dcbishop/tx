#ifndef TX_COLOUR_HPP
#define TX_COLOUR_HPP

class Colour {
	public:
		Colour();
		void setColour(float nred = 1.0, float ngreen = 1.0, float nblue = 1.0, float nalpha = 1.0);
		float getRed();
		float getGreen();
		float getBlue();
		float getAlpha();
		float red;
		float green;
		float blue;
		float alpha;
};

#endif // TX_COLOUR_HPP
