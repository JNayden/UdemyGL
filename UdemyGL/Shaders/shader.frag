#version 330 

in vec4 gCol;	
in vec2 TexCoord;

out vec4 colour;	

uniform sampler2D theTexture;

void main()					
{			
	//colour = gCol;	//vec4(1.0, 0.0, 0.0, 1.0); 
	colour = texture(theTexture, TexCoord) * gCol;
}