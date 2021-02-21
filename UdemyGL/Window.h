#pragma once
#include <stdio.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"


class Window
{
public:
	Window();
	Window(int windowWidth, int windowHeight);

	int Initialise();

	int getBufferWidth() { return bufferWidth; }
	int getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getKeys() { return keys; }
	float getXChange();
	float getYChange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();
private:
	GLFWwindow* mainWindow;

	int width, height;
	int bufferWidth, bufferHeight;

	bool keys[1024];

	float xChange, yChange;
	float lastX, lastY;
	bool mouseFirstMoved;
	
	void createCallBacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);// Handle function
	static void handleMouse(GLFWwindow* window, double xPos, double  yPos); // i change double to float
};

