#include <stdio.h>
#include <string.h>

#include <vector>
#include <cmath>

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"

//OpenGL library identifies what card drive i am already using

Window mainWindow;	
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

const float toRadians = 3.14159265f / 180.0f; // when we multiply something with this var is converted to radians

//Vertex Shader
static const char* vShader = "Shaders/shader.vert";//

//Fragment Shader
static const char* fShader = "Shaders/shader.frag";//

void CreateObjects()
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
void CreateShaders()
{
	Shader* shader1= new Shader();
	shader1->createfromFile(vShader, fShader);
	shaderList.push_back(*shader1);
}	

int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();//

	unsigned int uniformProjection = 0;//
	unsigned int uniformModel = 0;//

	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		//Get & Handle user input events
		glfwPollEvents();

		//Clear Window

		glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].useShader();
		uniformProjection = shaderList[0].getProjectionLocation();
		uniformModel = shaderList[0].getModelLocation();

		glm::mat4 model(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6, 0.4, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f); //Instead of creating new model we can use the current bcs of?
		model = glm::translate(model, glm::vec3(-0.0f, 1.0f, -3.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0));
		model = glm::scale(model, glm::vec3(0.6, 0.4, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); // attaching everything to a new model

		meshList[1]->RenderMesh();

		//	glUniform1f(uniformModel, basis);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}
	return 0;
}