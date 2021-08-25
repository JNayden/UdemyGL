#pragma once
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

#include "GL/glew.h"

class Shader
{
public:
	Shader();

	void createfromString(const char* vertexCode, const char* fragmenCode);
	void createfromFile(const char* vertexLocation, const char* fragmentLocation);
	std::string ReadFile(const char* filelocation);

	unsigned int getModelLocation();
	unsigned int getProjectionLocation();
	unsigned int getViewLocation(); ////
	unsigned int getAmbientIntensityLocation();
	unsigned int getAmbientColourLocation();
	unsigned int getDiffuseIntensityLocation();
	unsigned int getDirectionLocation();

	void useShader();
	void clearShader();

	~Shader();
private:
	unsigned int shaderID, uniformProjection, uniformModel, uniformView, uniformAmbientIntensity, 
		uniformAmbientColour, uniformDiffuseIntensity, uniformDirection;

	void CompileShaders(const char* vertexCode, const char* fragmenCode);
	void AddShader(unsigned int theProgram, const char* shaderCode, GLenum shaderType);
};

