#pragma once
#include "GL/glew.h"
#include <iostream>

class Shader
{
public:
	Shader();

	void createfromString(const char* vertexCode, const char* fragmenCode);

	unsigned int getModelLocation();
	unsigned int getProjectionLocation();

	void useShader();
	void clearShader();

	void createfromFile(const char* vertexLocation, const char* fragmentLocation);
	std::string ReadFile(const char* filelocation);

	~Shader();
private:
	unsigned int shaderID, uniformModel, uniformProjection;
	void CompileShaders(const char* vertexCode, const char* fragmenCode);
	void AddShader(unsigned int theProgram, const char* shaderCode, GLenum shaderType);
};

