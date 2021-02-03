#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if(!(x)) __debugbreak(); 
#define glCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
#include <iostream>
bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error: (" << error << "): " << function << " "
			<< file << ":" << line << std::endl;
		return false;
	}
	return true;
}


//Windows Dimension
const unsigned int width = 800, height = 600;

unsigned int VAO, VBO, shader; //VAO will holds  multiple vbo

//Vertex Shader
static const char* vShader = "					  \n\
#version 330 								      \n\
												  \n\
layout(location = 0) in vec3 pos;				  \n\
												  \n\
void main()										  \n\
{												  \n\
	gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0); \n\
}";
//Fragment Shader

static const char* fShader = "								  \n\
#version 330 												  \n\
															  \n\
out vec4 colour;											  \n\
															  \n\
void main()													  \n\
{															  \n\
	colour = vec4(1.0f, 0.0f, 0.0f, 1.0); \n\
}";

void CreateTriangle()
{
	float vertices[]
	{
		0.0f, 1.0f, 0.0f,
		-1.0, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glCall(glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(float), &vertices, GL_STATIC_DRAW));

	glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	glCall(glEnableVertexAttribArray(0));

	glCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // unbind VBO

	glCall(glBindVertexArray(0)); //unbind VAO

}
void AddShader(unsigned int program, const char* shaderCode, GLenum shaderType)
{
	unsigned int theShader = glCreateShader(shaderType);

	const char* theCode[1];
	theCode[0] = shaderCode;

	int codeLenght[1];
	codeLenght[0] = strlen(shaderCode);

	glShaderSourceCode(theShader, )
}
void CompileShader()
{
	shader = glCreateProgram();
	if (!shader)
	{
		printf("Error creating shader program");
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
		printf("Error linking program:  '&s'\n", eLog);
		return;
	}

	glValidateProgram(shader); //The shader we created it valid on the current CONTEXT the OpenGL is working in
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog); 
		printf("Error validating program:  '&s'\n", eLog);
		return;
	}
}

int main()
{
	//Initialise GLFW
	if(!glfwInit())
	{
		printf("GLFW Initialisation failed");
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
	if (!glfwInit())
	{
		printf("GLEW Initialisation failed");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	//Setup Viewport size
	glViewport(0, 0, bufferwidth, bufferheight);

	//Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Get & Handle user input events
		glfwPollEvents();

		//Clear Window

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	

		glfwSwapBuffers(mainWindow);

	}
	return 0;
}
// 1 Properties | Compat and OpenGL version
// 2 Actual WIndow | Create and Terminate
// 3 Buffersize 
// 4 Handel user input