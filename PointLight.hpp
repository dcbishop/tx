#ifndef TX_POINTLIGHT_HPP
#define TX_POINTLIGHT_HPP

#include "Object.hpp"
#include "Colour.hpp"

class PointLight : public Object {
	public:
		PointLight(string tag = DEFAULT_TAG, Visual* model = NULL);

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

#endif // TX_POINTLIGHT_HPP
