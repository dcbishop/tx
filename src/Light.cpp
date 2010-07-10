#include "Light.hpp"

Light::Light(string tag, Visual* model) {
	setTag(tag);
	setVisual(model);

	ambient.setColour(0.0, 0.0, 0.0, 1.0);
	diffuse.setColour(1.0, 1.0, 1.0, 1.0);
	specular.setColour(1.0, 1.0, 1.0, 1.0);
	emission.setColour(0.0, 0.0, 0.0, 1.0);

	setXYZ(0.0, 0.0, 1.0);
	setDirectional(0.0);

	setConstantAttenuation(1.0);
	setLinearAttenuation(0.0);
	setQuadraticAttenuation(0.0);
}

float Light::getDirectional() {
	return directional_;
}

float Light::getConstantAttenuation() {
	return constantAttenuation_;
}

float Light::getLinearAttenuation() {
	return linearAttenuation_;
}

float Light::getQuadraticAttenuation() {
	return quadraticAttenuation_;
}

void Light::setDirectional(float directional) {
	directional_ = directional_;
}

void Light::setConstantAttenuation(float constantAttenuation) {
	constantAttenuation_ = constantAttenuation;
}

void Light::setLinearAttenuation(float linearAttenuation) {
	linearAttenuation_ = linearAttenuation;
}

void Light::setQuadraticAttenuation(float quadraticAttenuation) {
	quadraticAttenuation_ = quadraticAttenuation;
}
