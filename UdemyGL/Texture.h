#pragma once
#include "GL/glew.h"

#include "stb_image.h"
#include <iostream>
#include <string.h>

class Texture
{
public:
	Texture();
	Texture(std::string fileLoc);

	void LoadTexture();
	void UseTexture();
	void ClearTexture();

	~Texture();
private:
	unsigned int textureID;
	int width, height, bitDepth;

	std::string fileLocation;
};

