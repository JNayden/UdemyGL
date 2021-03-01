#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"

class Light
{
public:
	Light();
	Light(float Red, float Green, float Blue, float aIntensity,
		  float xDir, float yDir, float zDir, float dIntensity);
	void UseLight(float ambientIntensityLocation, float ambientColourLocation,
				  float diffuseIntensityLocation, float directionLocation);

	~Light();
private:
	float ambientIntensity;
	glm::vec3 colour;

	float diffuseIntensity;
	glm::vec3 direction;
};

