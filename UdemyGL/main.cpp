#include <stdio.h>
#include <string.h>

#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include <vector>

// 1st Mesh class	GLsizei indeces
//					Create() incdices vertices numofi numofv
//				Renderer() 
	//				Delete()
// 2nd Shader Fstrem string/ 2 of the functions
// 3d Window for Predefenitions of GLFW



//glm::mat4 model(1.0f)
//OpenGL library identifies what card drive i am already using
//Windows Dimension

std::vector<Mesh*> meshList;
const unsigned int width = 800, height = 600;
const float toRadians = 3.14159265f / 180.0f; // when we multiply something with this var is converted to radians

unsigned int shader, uniformModel, uniformProjection; //VAO will holds  multiple VBOs


bool direction = true;
float basis = 0.0f;
float limit = 1.0f;
float increment = 0.0005f;

float curAngle = 0.0f;

bool directionScale = true;
float curSize = 0.1f;
float minSize = 0.1f;
float maxSize = 0.8f;

//Vertex Shader
static const char* vShader = "					  \n\
#version 330 								      \n\
												  \n\
layout (location = 0) in vec3 pos;				  \n\
out vec4 gCol;									  \n\
												  \n\
uniform mat4 model;							      \n\
uniform mat4 projection;											  \n\
												  \n\
void main()										  \n\
{												  \n\
	gl_Position = projection * model * vec4(pos, 1.0);  \n\
	gCol = vec4(clamp(pos, 0.5f, 1.0f), 1.0f);										\n\
}";
//Fragment Shader

static const char* fShader = "								  \n\
#version 330 												  \n\
															\n\
in vec4 gCol;															\n\
															  \n\
out vec4 colour;											  \n\
															  \n\
void main()													  \n\
{															  \n\
	colour = gCol;				//vec4(1.0, 0.0, 0.0, 1.0); \n\
}";

void CreateTriangle()
{
	unsigned int indices[]
	{
		0, 2, 3,	//0,3,1,//
		2, 1, 3,	//1,3,2,//
		0, 1, 3,	//2,3,0,//
		0, 1, 2		//0,1,2 //
	};
	float vertices[]
	{									  //
		-1.0f, -1.0f, 0.0f, //0
		0.0f, -1.0f, 1.0f, // 1
		1.0f, -1.0f, 0.0f, // 2			  //
		0.0f, 1.0f, 0.0f   // 3    //            //
	};
	Mesh* obj1 = new Mesh(); //calloc vs malloc
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh(); //calloc vs malloc
	obj2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);
}
void AddShader(unsigned int theProgram, const char* shaderCode, GLenum shaderType)
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
void CompileShaders()
{
	shader = glCreateProgram();
	if (!shader)
	{
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	int result = 0;
	char eLog[1024] = { 0 };

	glLinkProgram(shader); //Makes executables on graphics card
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog); //info for program pass into the eLog;
		printf("Error linking program: '&s'\n", eLog);
		return;
	}

	glValidateProgram(shader); //The shader we created it valid on the current CONTEXT the OpenGL is working in
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '&s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shader, "model");
	uniformProjection = glGetUniformLocation(shader, "projection");
}

int main()
{
	//Initialize GLFW
	if (!glfwInit())
	{
		printf("GLFW Initialization failed");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Core profile = No Backward Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(width, height, "Test window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW Window creation failed");
		glfwTerminate;
		return 1;
	}

	//Get buffer size information
	int bufferwidth, bufferheight;
	glfwGetFramebufferSize(mainWindow, &bufferwidth, &bufferheight);

	//Set context for GLEW to use

	glfwMakeContextCurrent(mainWindow);

	//Allow modern extension features

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("GLEW initialization failed");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	//Setup Viewport size
	glViewport(0, 0, bufferwidth, bufferheight);
	CreateTriangle();
	CompileShaders();

	glm::mat4 projection = glm::perspective(45.0f, (float)bufferwidth / (float)bufferheight, 0.1f, 100.0f);

	//Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Get & Handle user input events
		glfwPollEvents();

		if (direction)
		{
			basis += increment * 0.2;
		}
		else
		{
			basis -= increment * 0.2;
		}
		if (abs(basis) >= limit)
		{
			direction = !direction;
		}

		curAngle += 0.05f;
		if (curAngle >= 360)
		{
			curAngle -= 360;
		}

		if (directionScale)
		{
			curSize += 0.001f;
		}
		else
		{
			curSize -= 0.001f;
		}

		if (curSize >= maxSize || curSize <= minSize)
		{
			directionScale = !directionScale;
		}

		//Clear Window

		glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader);

		glm::mat4 model(1.0f);


		model = glm::translate(model, glm::vec3(basis, 0.0f, -3.0f));
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4, 0.4, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f); //Instead of creating new model we can use the current bcs of?
		model = glm::translate(model, glm::vec3(-basis, 1.0f, -3.0f));
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4, 0.4, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[1]->RenderMesh();

		//	glUniform1f(uniformModel, basis);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}
	return 0;
}
// 1 Properties | Compatibility and OpenGL version
// 2 Actual WIndow | Create and Terminate
// 3 Buffer-size 
// 4 Handel user input 

// Why we have to use projection matrix?
		// How we changing constantly our axises bs of what?
		// What happen when replace position of doing on rotate and translate?