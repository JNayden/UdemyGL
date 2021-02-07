#include "Shader.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}
void Shader::createfromString(const char* vertexCode, const char* fragmenCode)
{
	CompileShaders(vertexCode, fragmenCode);
}

void Shader::createfromFile(const char* vertexLocation, const char* fragmentLocation)//
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShaders(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLocation)//
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);
	if (!fileStream.is_open())
	{
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
		//i assume that the next while is for making a new line if it's the end of line
	}
	std::string line;
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

void Shader::CompileShaders(const char* vertexCode, const char* fragmenCode)
{
	shaderID = glCreateProgram();
	if (!shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmenCode, GL_FRAGMENT_SHADER);

	int result = 0;
	char eLog[1024] = { 0 };

	glLinkProgram(shaderID); //Makes executables on graphics card
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog); //info for program pass into the eLog;
		printf("Error linking program: '&s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID); //The shader we created it valid on the current CONTEXT the OpenGL is working in
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '&s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
}

unsigned int Shader::getProjectionLocation()
{
	return uniformProjection;
}

unsigned int Shader::getModelLocation()
{
	return uniformModel;
}


void Shader::AddShader(unsigned int theProgram, const char* shaderCode, GLenum shaderType)
{
	unsigned int theShader = glCreateShader(shaderType);

	const char* theCode[1];
	theCode[0] = shaderCode;

	int codeLenght[1];
	codeLenght[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLenght);
	glCompileShader(theShader);

	int result = 0;
	char eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog); //info for program pass into the eLog;
		printf("Error compiling the %d shader:  '&s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}
void Shader::useShader()
{
	glUseProgram(shaderID);
}

void Shader::clearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
	uniformModel = 0;
	uniformProjection = 0;
}

Shader::~Shader()
{
	clearShader();
}