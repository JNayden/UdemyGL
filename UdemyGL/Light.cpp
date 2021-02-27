#include "Light.h"

//1 
//glm::vec3 colour(1.0f, 1.0f, 1.0f) if there is a colour it's gonna show on the it for us
Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
}
Light::Light(float red, float green, float blue, float aIntensity)
{
	colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
}

void Light::UseLight(float ambientIntensityLocation, float ambientColourLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
}
Light::~Light()
{

}