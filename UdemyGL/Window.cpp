#include "Window.h"
#include <stdio.h>
#include <windows.h>
Window::Window()
{
	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = false; // false or 0
	}
}
Window::Window(int windowWidth, int windowHeight)
{
	//-N-
	width = windowWidth;
	height = windowHeight;
	//for (size_t i = 0; i < 1024; i++)
	//{
	//	keys[i] = false;				am i needed
	//}
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

	//Handel key + Mouse input

	createCallBacks();

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
	glfwSetWindowUserPointer(mainWindow, this); //pointer to Handle
}

void Window::createCallBacks()
{
	glfwSetKeyCallback(mainWindow, HandleKeys);
}

void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	//	get "this" from above and then pass it to the window and now we can access key massive
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] == true;
			printf("Pressed: %i\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] == false;
			printf("Released: %i\n", key);
		}
	}
}

//Usage of Handle
//strange assignemnt
// GLFW key functions

Window::~Window()
{
 	glfwDestroyWindow(mainWindow);
	glfwTerminate(); 
}