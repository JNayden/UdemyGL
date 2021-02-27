#version 330 

in vec4 gCol;	
in vec2 TexCoord;

out vec4 colour;	

struct DirectionalLight
{
	vec3 colour;
	float ambientIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;

void main()					
{			
	//colour = gCol;	//vec4(1.0, 0.0, 0.0, 1.0); 
	//colour = texture(theTexture, TexCoord);// * gCol;
	
	vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;
	colour = texture(theTexture, TexCoord) * ambientColour;
}