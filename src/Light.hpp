#ifndef TX_Light_HPP
#define TX_Light_HPP

#include "Object.hpp"
#include "Colour.hpp"

class Light : public Object {
	public:
		Light(string tag = DEFAULT_TAG, Visual* model = NULL);

		float getDirectional();
		float getConstantAttenuation();
		float getLinearAttenuation();
		float getQuadraticAttenuation();
		void setDirectional(float d);
		void setConstantAttenuation(float ca);
		void setLinearAttenuation(float la);
		void setQuadraticAttenuation(float qa);

		Colour ambient;
		Colour diffuse;
		Colour specular;
		Colour emission;

	private:
		float directional_;
		float constantAttenuation_;
		float linearAttenuation_;
		float quadraticAttenuation_;
};

#endif // TX_Light_HPP
