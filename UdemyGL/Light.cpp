#include "Light.h"

//1 
//glm::vec3 colour(1.0f, 1.0f, 1.0f) if there is a colour it's gonna show on the it for us
Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	diffuseIntensity = 0.0f;
}
Light::Light(float red, float green, float blue, float aIntensity, 
			 float xDir, float yDir, float zDir, float dIntensity)
{
	colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;

	direction = glm::vec3(xDir, yDir, zDir);
	diffuseIntensity = dIntensity;
}

void Light::UseLight(float ambientIntensityLocation, float ambientColourLocation,
					 float diffuseIntensityLocation, float directionLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);	

	glUniform3f(directionLocation, colour.x, colour.y, colour.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}
Light::~Light()
{

}