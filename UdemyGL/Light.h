#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"

class Light
{
public:
	Light();
	Light(float Red, float Green, float Blue, float aIntensity);
	void UseLight(float ambientIntensityLocation, float ambientColourLocation);
	~Light();
private:
	float ambientIntensity;
	glm::vec3 colour;
};

