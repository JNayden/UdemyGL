#include "Window.h"
#include <stdio.h>
#include <windows.h>
Window::Window()
{
	width = 800;
	height = 600;

	mouseFirstMoved = false;
	xChange = 0.0f;
	yChange = 0.0f;
	lastX = 0.0f;
	lastY = 0.0f;

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

	mouseFirstMoved = false;
	xChange = 0.0f;
	yChange = 0.0f;
	lastX = 0.0f;
	lastY = 0.0f;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = false;			//	am i need it
	}
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
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	glfwSetCursorPosCallback(mainWindow, HandleMouse);
}
float Window::getXChange()		  //??
{								  //??
	float theChange = xChange;	  //??
	xChange = 0.0f;				  //??
	return theChange;			  //??
}								  //??
float Window::getYChange()		  //??
{								  //??
	float theChange = yChange;	  //??
	yChange = 0.0f;				  //??
	return theChange;			  //??
}								  //??

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
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] == false;
		}
	}
}
void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos) // ichange double to float
{	// change xpos last x
	//firstMoved lastx lasty the change that we have to evaluate
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}
	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = yPos - theWindow->lastY;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	//printf("x:%.6f, y:%.6f\n", theWindow->xChange, theWindow->yChange);
}

//Usage of Handle
//strange assignemnt
// GLFW key functions

Window::~Window()
{
 	glfwDestroyWindow(mainWindow);
	glfwTerminate(); 
}