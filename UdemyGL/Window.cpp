#include "Window.h"
#include <stdio.h>
Window::Window()
{
	width = 800;
	height = 600;
}
Window::Window(int windowWidth, int windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

int Window::Initialise()
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

	mainWindow = glfwCreateWindow(width, height, "Test window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW Window creation failed");
		glfwTerminate;
		return 1;
	}

	//Get buffer size information
	
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

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
	glViewport(0, 0, bufferWidth, bufferHeight);
}
Window::~Window()
{
 	glfwDestroyWindow(mainWindow);
	glfwTerminate(); 
}