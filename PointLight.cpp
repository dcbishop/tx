#include "PointLight.hpp"

PointLight::PointLight(string tag, Visual* model) {
	directional_ = 1.0;
	setTag(tag);
	setVisual(model);
	#warning ['TODO']: Set some sane defaults...
}

float PointLight::getDirectional() {
	return directional_;
}

float PointLight::getConstantAttenuation() {
	return constantAttenuation_;
}

float PointLight::getLinearAttenuation() {
	return linearAttenuation_;
}

float PointLight::getQuadraticAttenuation() {
	return quadraticAttenuation_;
}

void PointLight::setDirectional(float directional) {
	directional_ = directional_;
}

void PointLight::setConstantAttenuation(float constantAttenuation) {
	constantAttenuation_ = constantAttenuation;
}

void PointLight::setLinearAttenuation(float linearAttenuation) {
	linearAttenuation_ = linearAttenuation;
}

void PointLight::setQuadraticAttenuation(float quadraticAttenuation) {
	quadraticAttenuation_ = quadraticAttenuation;
}
